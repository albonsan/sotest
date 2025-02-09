- Application source code:  
Please refer to interpreter.c

- Libraries source code:  
Please refer to tetslib01.c and testlib02.c

- Script used for testing:  
Please refer to testscript.sc

- Compilation instructions:
  - Compile tetslib01.c and testlib02.c files to generate the tetslib01.so and tetslib02.so libs.     $ gcc -shared -o testlib01.so -fPIC testlib01.c  
  $ gcc -shared -o testlib02.so -fPIC testlib02.c

  - Compile the interpreter.c file.  
  $ gcc -o interpreter interpreter.c -ld

  - Execute the script.  
  $ ./interpreter testscript.sc

- Screenshot evidence:  
Please find the screenshots in the /evidence directory  

**Compilation:**  
![img-compilation](/evidence/compilation.png)  

**Script execution:**  
![img-execution](/evidence/execution_script.png)  

**Interactive execution:**  
![img-interactive](/evidence/execution_interactive.png)  

**Validations:**  
![img-validations](/evidence/validations.png)
