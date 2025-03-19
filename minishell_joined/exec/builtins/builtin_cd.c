/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:18 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:20 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* ------------------------------------------------------------------------
   1) Función para obtener el valor de una variable en la lista t_env
   ------------------------------------------------------------------------ */
   char *get_env_value(t_env *env, const char *varname)
   {
       while (env)
       {
           if (strcmp(env->name, varname) == 0)
               return env->content;  // Devuelve un puntero a la cadena (¡no modifiques directamente!)
           env = env->next;
       }
       return NULL;  // Si no la encuentra
   }
   
   /* ------------------------------------------------------------------------
      2) Función para actualizar (o crear) una variable en t_env
      ------------------------------------------------------------------------ */
   void update_env_value(t_env **env, const char *varname, const char *new_content)
   {
       t_env *tmp = *env;
   
       // Buscar si ya existe
       while (tmp)
       {
           if (strcmp(tmp->name, varname) == 0)
           {
               // Liberamos antiguo content y asignamos el nuevo
               free(tmp->content);
               tmp->content = strdup(new_content);
               return;
           }
           tmp = tmp->next;
       }
   
       // Si no existe, creamos un nuevo nodo
       t_env *new_node = (t_env *)malloc(sizeof(t_env));
       if (!new_node)
       {
           perror("update_env_value");
           return; // Maneja error a tu manera
       }
       new_node->name = strdup(varname);
       new_node->content = strdup(new_content);
       new_node->next = *env;
       *env = new_node;
   }
   
   /* ------------------------------------------------------------------------
      3) Función para expandir la tilde ('~') usando el valor de "HOME"
      ------------------------------------------------------------------------ */
   static char *expand_tilde(const char *arg, t_env *env)
   {
       const char *home = get_env_value(env, "HOME");
   
       if (!home)
       {
           // Si no hay HOME, consideramos error (o puedes decidir no hacerlo)
           write(2, "cd: HOME not set\n", 17);
           return NULL;
       }
       // cd ~
       if (strcmp(arg, "~") == 0)
           return strdup(home);
   
       // cd ~/
       if (strncmp(arg, "~/", 2) == 0)
       {
           size_t len = strlen(home) + strlen(arg + 1) + 1;
           char *expanded = malloc(len);
           if (!expanded)
           {
               perror("cd");
               return NULL;
           }
           strcpy(expanded, home);
           strcat(expanded, arg + 1); // El +1 salta el '~'
           return expanded;
       }
       // Si no matchea, devolvemos copia tal cual
       return strdup(arg);
   }
   
   /* ------------------------------------------------------------------------
      4) Actualizar OLDPWD y PWD en la lista t_env (sin setenv)
      ------------------------------------------------------------------------ */
   static int update_pwd_oldpwd(t_env **env, const char *oldpwd)
   {
       // getcwd(NULL, 0) pide a libc que reserve dinamicamente
       char *cwd = getcwd(NULL, 0);
       if (!cwd)
       {
           perror("cd");
           return 1;
       }
   
       // 1) Actualizamos OLDPWD
       update_env_value(env, "OLDPWD", oldpwd);
   
       // 2) Actualizamos PWD
       update_env_value(env, "PWD", cwd);
   
       free(cwd);
       return 0;
   }
   
   /* ------------------------------------------------------------------------
      5) Manejar "cd -": usa OLDPWD y lo imprime, si existe
      ------------------------------------------------------------------------ */
   static char *handle_cd_minus(t_env *env)
   {
       char *oldpwd = get_env_value(env, "OLDPWD");
   
       if (!oldpwd)
       {
           write(2, "cd: OLDPWD not set\n", 19);
           return NULL;
       }
       // Imprimimos oldpwd seguido de nueva línea
       write(1, oldpwd, strlen(oldpwd));
       write(1, "\n", 1);
   
       return oldpwd; // devolvemos para hacer chdir()
   }
   
   /* ------------------------------------------------------------------------
      6) El builtin_cd principal, sin setenv/getenv, usando t_env **env
      ------------------------------------------------------------------------ */
   int builtin_cd(char **args, t_env **env)
   {
       char *oldpwd = getcwd(NULL, 0);  // Guardamos el directorio actual
       char *path = NULL;
       char *expanded = NULL;
   
       if (!oldpwd)
       {
           perror("cd");
           return 1;
       }
   
       /* CASO: sin argumentos → ir a $HOME */
       if (!args || !args[0])
       {
           path = get_env_value(*env, "HOME");
           if (!path)
           {
               write(2, "cd: HOME not set\n", 17);
               free(oldpwd);
               return 1;
           }
       }
       /* Si hay más de un argumento => error */
       else if (args[1])
       {
           write(2, "cd: too many arguments\n", 24);
           free(oldpwd);
           return 1;
       }
       /* cd - */
       else if (strcmp(args[0], "-") == 0)
       {
           path = handle_cd_minus(*env);
           if (!path)
           {
               free(oldpwd);
               return 1;
           }
       }
       /* Expandir ~ */
       else
       {
           expanded = expand_tilde(args[0], *env);
           if (!expanded)
           {
               free(oldpwd);
               return 1;
           }
           path = expanded;
       }
   
       /* Cambiar directorio */
       if (chdir(path) == -1)
       {
           perror("cd");
           free(oldpwd);
           free(expanded);
           return 1;
       }
   
       /* Actualizar PWD y OLDPWD en nuestra lista t_env */
       if (update_pwd_oldpwd(env, oldpwd) != 0)
       {
           free(oldpwd);
           free(expanded);
           return 1;
       }
   
       free(oldpwd);
       free(expanded);
       return 0; // Éxito
   } 