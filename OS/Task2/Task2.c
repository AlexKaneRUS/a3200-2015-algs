#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
 
 
#define BUFFERSIZE 1024
#define COPYMORE 0644
 
 
 
 
int copyDir(char *src, char *dest);
int copyFiles(char *src, char *dest);
int dostat(char *filename);
int mode_isReg(struct stat info);
 
 
 
 
int main(int ac, char *av[])
{

  if(ac != 3)
  {
    fprintf(stderr, "usage: %s source destination\n", *av);
    exit(1);
  }
 
   char src[PATH_MAX+1];
   strcpy(src, av[1]);
   char dest[PATH_MAX+1];
   strcpy(dest, av[2]);
 
   if( src[0] != '/' && dest[0] != '/' )//cp1 file1.txt file2.txt
   {
       copyFiles(src, dest);
   }
   else if( src[0] != '/' && dest[0] == '/' )//cp1 file1.txt /dir 
   { 
      strcat(dest, "/");
      strcat(dest, src);
 
      
      copyFiles(src, dest);
  }
  else //cp1 /dir1 /dir2    
  {                        
      copyDir(src, dest);     
  }
}
 
 
int copyDir(char *source, char *destination)
{
    DIR *dir_ptr = NULL;
    struct dirent *direntp;
    char tempDest[strlen(destination)+228];
    char tempSrc[strlen(source)+228];
    strcat(destination, "/");      
    strcpy(tempDest, destination);
    strcat(source, "/");
    strcpy(tempSrc, source);  
    
    struct stat fileinfo;
 
 
   if( (dir_ptr = opendir(source)) == NULL )
   {
      fprintf(stderr, "cp1: cannot open %s for copying\n", source);
      return 0;
   }
   else
   {
      while( (direntp = readdir(dir_ptr)))
      {      
       

          strcat(tempDest, direntp->d_name);        
          strcat(tempSrc, direntp->d_name);
          copyFiles(tempSrc, tempDest);
          strcpy(tempDest, destination);
          strcpy(tempSrc, source);            

      }
      closedir(dir_ptr);
      return 1;
   }
 
 
}
 
int copyFiles(char *source, char *destination)
{

  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
 
  in_fd=open(source, O_RDONLY);
 
  out_fd=creat(destination, COPYMORE);
 
 
  while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 )
  {
    write(out_fd, buf, n_chars);
  }
 
 
   close(in_fd);
   close(out_fd);
 
 
   return 1;
}
