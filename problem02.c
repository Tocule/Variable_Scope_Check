#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 10

int counter=0;
int counter1=0;

typedef struct variable
{
    char variable_name[5];
    int defined;
    int used;
}Variables;

typedef struct scope
{
    int number_of_variables;
    int scope;
    Variables v[5];
}Scope;

Scope s[MAX];

int main(void)
{
     FILE *fp;
     int i,j,k;
     char buffer[20];
     char *p;
     char check[]="{";
     char check1[]="int";
     char check2[]="=";
     char check3[]="}";

     int count=0;
     int flag=0;
     int flag1=0;
     char check_var_name[5];
     for(i=0;i<MAX;i++)
     {
	s[i].number_of_variables=0;
	s[i].scope=0;
     }	
     fp=fopen("example04.c","r");
     if(fp==NULL)
     {
	printf("Couldn't open the file\n");
	exit(0);
     }
	
     fscanf(fp,"%s",buffer);
     while(!feof(fp))
     {
	  if(strcmp(buffer,check)==0)
	  {	  
	       counter++;
     	       for(i=0;i<counter;i++)
	       {
		   s[i].scope++;
    	       }
	 }
         if(strcmp(buffer,check1)==0)
	 {
		 
		fscanf(fp,"%s",buffer);
		if(counter>1)
		{
		   i=0;
                   while(buffer[i]!=';')
		   { 
		      check_var_name[counter1]=buffer[i];
	   	      i++;
		      counter1++;
		   }
     		   check_var_name[counter1]='\0';
		   counter1=0;

		   for(i=0;i<counter;i++)
     		   {
        		for(j=0;j<s[i].number_of_variables;j++)
			{
			    if(strcmp(s[i].v[j].variable_name,check_var_name)==0)
			    {
				flag1=1;
			    }				
			}		 
		   }
   		}	
    	        if(flag1==0)
		{		
			i=0;
			while(buffer[i]!=';')
			{	
			   s[counter-1].v[s[counter-1].number_of_variables].variable_name[counter1]=buffer[i];
			   i++;
			   counter1++;
			}   
   			//printf("%s\n",s[counter].v[s[counter].number_of_variables].variable_name);	   
			s[counter-1].v[s[counter-1].number_of_variables].variable_name[counter1]='\0';
			s[counter-1].v[s[counter-1].number_of_variables].defined=1;
			s[counter-1].number_of_variables++;
			counter1=0;
		}
		flag1=0;	
	}
	fscanf(fp,"%s",buffer);
     }	
     /*
     for(i=0;i<counter;i++)
     {   
	printf("%d\n",s[i].number_of_variables);     
	for(j=0;j<s[i].number_of_variables;j++)
        {
		printf("Variable name : %s\n",s[i].v[j].variable_name);
		printf("number of var : %d\n",s[i].number_of_variables);
		printf("Scope : %d\n",s[i].scope);
	}
    }
    */
     
    rewind(fp);
    char buffer1[10];
    int line_counter=0;
    int t;
    fgets(buffer,20,fp);
    while(!feof(fp))
    {
	line_counter++;  
      //  printf("%s",buffer);	
	p=strstr(buffer,check3);
        if(p)
	{
	    for(i=0;i<counter;i++)
	    {
		s[i].scope--;
    	    }
	}
	p=strstr(buffer,check2);
	if(p)
	{
	    for(i=0;i<counter;i++)
	    {
		for(j=0;j<s[i].number_of_variables;j++)
	    	{
		    p=strstr(buffer,s[i].v[j].variable_name);
    		    if(p)
		    {
			if(s[i].scope<=0)
	    		{
			    for(t=0;!isalpha(buffer[t]);t++)
	    		    {

    			    }				
			    for(k=0;buffer[t]!='\n';k++)
			    {
				buffer1[k]=buffer[t];
				t++;
		    	    }
	    		    buffer1[k]='\0';		    
			    flag=1;
			    printf("Line:%d %s ===> %s is not defined\n\n",line_counter,buffer1,s[i].v[j].variable_name);
			   // printf("Line:%d %s\n",line_counter,s[i].v[j].variable_name);
			}
		    }
		}
	    }
        }
	fgets(buffer,20,fp);
    }

    if(flag==0)
    {
	printf("Valid\n");
    }	

}     
