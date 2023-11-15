#include "Shell.h"

    /
     * _myexit - function that exit from the shell
     * @import: structure parameter
     * Return: given exit status 
    */
    int _myexit(import_t *import)
    {
        int exitcheck;

        if (import->argv[1])
        {
            exitcheck = _errtoi(import->argv[1]);
            if (exitcheck == -1)
            {
                import->status = 2;
                print_error(import, "Illegal number: ");
                _eputs(import->argv[1]);
                _eputchar('\n');
                return (1);
            }
            import->err_num = _errtoi(import->argv[1]);
            return (-2);
        }
        import->err_num = -1;
        return (-2);
    }
    /
     * _mycd - do the cd command 
     * @import: structer parameter
     * Return: 0 (sucess)
    */
    int _mycd(import_t *import)
    {
        char *n, *dir, buffer[1024];
        int chdir_ret;

        n = getcwd(buffer, 1024);
        if (!n)
            _puts("TODO: >>getcwd failure emsg here<<\n");
        if (!import->argv[1])
        [
            dir = _getenv(import, "HOME=");
            if (!dir)
                chdir_ret = chdir((dir = _getenv(import, "PWD=")) ? dir : "/");
            else
                chdir_ret = chdir(dir);
        ]
        else if (_strcmp(import->argv[1], "-") == 0)
        {
            if (!_getenv(import, "OLDPWD="))
            {
                _puts(n);
                _putchar('\n');
                return (1);
            }
            _puts(_getenv(import, "OLDPWD=")), _putchar('\n');
            chdir_ret = chdir((dir = _getenv(import, "OLDPWD=")), ? dir : "/");
        }
        else
        chdir_ret = chdir(import->argv[1]);
        if (chdir_ret == -1)
        {
            print_error(import, "can't cd to");
            _eputs(import->argv[1], _eputchar('\n'));
        }
        else
        {
            _setenv(import, "OLDPWD", _getenv(import, "PWD="));
            _setenv(import, "PWD", getcwd(buffer, 1024));
        }
        return (0);
    }
    /**
     * _myhelp - function changes the current dir 
     * @import: struct parameter
     * Return: 0 always success 
    */
    int _myhelp(import_t *import)
    {
        char **arg_array;

        arg_array = import->argv;
        _puts("help call works. Function not yet implemented \n");
        if (0)
            _puts(*arg_array);
        return (0);
    }
