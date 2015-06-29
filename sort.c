#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "my402list.h"
#include "cs402.h"
#include "my402list.c"

typedef struct myinfo{
    char tran[5];
    time_t tran_time;
    char tran_amount[12];
	char tran_desc[30];
}myinfo;

int sort_list(My402List* dum_list)
{
	int chk=0; int len=0; int i=0; int j=0; int t1=0;int t2=0;
	void* temp_obj=NULL; int flag=1;
	chk=My402ListEmpty(dum_list);
	My402ListElem *elem=NULL;
	myinfo* m3=(myinfo*) malloc(sizeof(myinfo));
	myinfo* m4=(myinfo*) malloc(sizeof(myinfo));
	
	if(chk==TRUE)
	{
		printf("\nEmpty list no sorting needed");
		return FALSE;
	}	
	else
	{
		len=My402ListLength(dum_list);
		
		while(flag)
		{
			flag=0;
			elem=My402ListFirst(dum_list);
			
			while((elem->next)!=&(dum_list->anchor))
			{
			  m3=((myinfo*)(elem->obj));
			  m4=((myinfo*)(elem->next->obj));
			
				if((m3->tran_time) > (m4->tran_time))
				{
					//swap
					temp_obj=elem->obj;
					elem->obj=elem->next->obj;
					elem->next->obj=temp_obj;
					flag=1;
				}	
				elem=elem->next;
				i++;
			}	
		}
	}	
	return TRUE;
}

void display_list(My402List* dum_list)
{
	//list
	int chk=0; int i=0; int len=0; int p=0;
	char t1[30];
	memset(t1, 0, 30);
	char t2[30];
	memset(t2, 0, 30);
	char t3[30];
	memset(t3, 0, 30);
	char t4[30];
	memset(t4, 0, 30);
	char t5[30];
	memset(t5, 0, 30);
	char t6[30];
	memset(t6, 0, 30);
	My402ListElem *elem=NULL; 
	int len2=0;	int len_am=0; int len_bal=0; int w=0,x=0,z=0;int c=0;
	char tok_str[5][10];
	memset(tok_str, 0, 50);
	char *tim;
	char tim2[50];int k=0;
	memset(tim2, 0, 50);
	float balance=0.0;
	float amount=0.0;
	
	chk=My402ListEmpty(dum_list);
	myinfo* m2=(myinfo*) malloc(sizeof(myinfo));
	if(chk==TRUE)
		printf("\nList is empty, nothing to print");
	else
	{
		 printf("\n+-----------------+--------------------------+----------------+----------------+");
		printf("\n|       Date      | Description              |         Amount |        Balance |");
		printf("\n+-----------------+--------------------------+----------------+----------------+");
		
		len=My402ListLength(dum_list);
		for(elem=My402ListFirst(dum_list),c=0;c<len ; elem=elem->next,c++)
		{
			memset(tim2, 0, 50);
			
			m2=((myinfo*)(elem->obj)); 
			//printf("\nValue 1 is %s",m2->tran);
			fflush(stdout);
			tim=ctime(&(m2->tran_time));
			
			if(tim[(strlen(tim))-1] == '\n')
				tim[(strlen(tim))-1] = '\0';
			//printf("\nTime %s",tim);
			strcpy(tok_str[0],strtok(tim," "));
			strcpy(tok_str[1],strtok(NULL," "));
			strcpy(tok_str[2],strtok(NULL," "));
			strcpy(tok_str[3],strtok(NULL," "));
			strcpy(tok_str[4],strtok(NULL," "));
			
			strcat(tim2,tok_str[0]);
			strcat(tim2," ");
			strcat(tim2,tok_str[1]);
			strcat(tim2," ");
			strcat(tim2,tok_str[2]);
			strcat(tim2," ");
			strcat(tim2,tok_str[4]); 
			//strcat(tim2,"\0");
			//k=strlen(tim2);
			//tim2[k]='\0';
			if(tim2[(strlen(tim2))-1] == '\n')
				tim2[(strlen(tim2))-1] = '\0';
			else
				tim2[(strlen(tim2))]='\0';
			
			//printf("\nValue 2 is %s",tim2);
			fflush(stdout);
			
			printf("\n| %s",tim2);
			printf(" | ");
			
			//printf("\nHere");
			//printf("\nValue 3 is %s",m2->tran_amount);
			printf("%24.24s | ",m2->tran_desc);
			
			//printf("\nValue 4 is %s",m2->tran_desc);
			strncpy(t1,m2->tran_amount,sizeof(m2->tran_amount));
			for(i=0,p=0;t1[i]!='\0';i++)
			 {
				if(t1[i]=='.')
				{
				  if(p>7)
				  {
					//?????? displayed
					printf("(?,???,???.\?\?) | ");
					printf("(?,???,???.\?\?) |");
				  }	  
				  else if(t1[i+3]!='\0')
				  {
					printf("\nOnly 2 digits allowed after decimal...exiting...");
					exit(1);
				  }	  
				}
				else
				{
					p=p+1;
				}
			 } 
			 
			amount=atof(m2->tran_amount);
			//printf("\nAmount =%2f",amount);
			//amount=roundf(amount * 100) / 100;
			
			strncpy(t5,m2->tran_amount,sizeof(m2->tran_amount));
			len_am=strlen(t5);
			if(len_am==4 || len_am==5 || len_am==6)
			{
			  strncpy(t3,t5,sizeof(t5));
			}
			else
			{
			  if(len_am==7 || len_am==8 || len_am==9)
			  {
				z=0;
				for(w=len_am,x=len_am-1;x>=0;w--,z++)
				{
				  if(z<6)
				  {
					t3[w]=t5[x];
					x--;
				  }		
				  if(z==6)
					  t3[w]=',';
				  if(z>6)
				  {
					 t3[w]=t5[x];
					 x--;
				  }
				}
			  }
			  else
			  {
				z=0;
				for(w=len_am,x=len_am-1;x>=0;w--,z++)
				{
				  if(z<6)
				  {
					t3[w]=t5[x];
					x--;
				  }		
				  if(z==6 || z==10)
					  t3[w]=',';
				  if(z>6 && z!=10)
				  {
					 t3[w]=t5[x];
					 x--;
				  }
				}
			  }
			}
			t3[len_am+1]='\0';
			
			
			 strncpy(t2,m2->tran,sizeof(m2->tran)); 
			 if(t2[0]=='+')
			 {
				printf("%13s ",t3);
				balance=balance+amount;
			 }	
			 
			 if(t2[0]=='-')
			 {
				printf("(%12s)",t3);
				balance=balance-amount;
			 }
			 
			//printf(" | "); 
			    
			//balance=roundf(balance * 100) / 100;
				
			snprintf(t6,sizeof(t6),"%.2f",balance);
			
			len_bal=strlen(t6);
			t6[len_bal]='\0';
			//printf("\nBalance %s",t6);
			if(len_bal==4 || len_bal==5 || len_bal==6)
			{
			  strncpy(t4,t6,sizeof(t6));
			}
			else
			{
			  if(len_bal==7 || len_bal==8 || len_bal==9)
			  {
				z=0;
				for(w=len_bal,x=len_bal-1;x>=0;w--,z++)
				{
				  if(z<6)
				  {
					t4[w]=t6[x];
					x--;
				  }		
				  if(z==6)
					  t4[w]=',';
				  if(z>6)
				  {
					 t4[w]=t6[x];
					 x--;
				  }
				}
			  }
			  else
			  {
				z=0;
				for(w=len_bal,x=len_bal-1;x>=0;w--,z++)
				{
				  if(z<6)
				  {
					t4[w]=t6[x];
					x--;
				  }		
				  if(z==6 || z==10)
					  t4[w]=',';
				  if(z>6 && z!=10)
				  {
					 t4[w]=t6[x];
					 x--;
				  }
				}
			  }
			}
			t4[len_bal+1]='\0';
			
				 if(balance>9999999)
				{
				  printf("(?,???,???.\?\?) |");
				}	
				
				else 
				{
					 if(balance>=0)
					 {
					  printf(" | %13s  |",t4);
					 }
				
					 else
					 {
					  printf(" | (%12s) |",t4);
					 }
			    } 
		}	
		printf("\n+-----------------+--------------------------+----------------+----------------+");
	}	
	
}
	
	
void display_final(My402List* dum_list)
{
	//display the output reqd
	

	
}	

void read_file(My402List* dum_list,FILE *fp)
{
	int i=0; int chk=0; int len=0; int k1=0; int k2=0;
	time_t cur_time;  int l2=0;
	char t1[30]; char t2[30]; int j=0; int p=0; char t3[5];char t9[30];
    memset(t1, 0, 30); memset(t2, 0, 30); memset(t3, 0, 5);memset(t9, 0, 30);
	char file_buf[1026];
    memset(file_buf, 0, 1026);
	char timer[20];
	memset(timer, 0, 20);
	My402ListElem *elem=NULL;
	myinfo* m3=(myinfo*) malloc(sizeof(myinfo));
	//printf("\nIn fn name %s ",file_name);
	//fp = fopen(file_name,"r"); // read mode
			  if( fp == NULL )
			   {
				  perror("\nError while opening the tfile\n");
				  exit(1);
			   }

	while(fgets(file_buf,sizeof(file_buf),fp)!=NULL)
	{
		//memset(t1, 0, 30); memset(t2, 0, 30); memset(t3, 0, 5);
		memset(t9, 0, 30);
		//memset(timer, 0, 20);
		len=strlen(file_buf);
		if(len>1024)
		{
			perror("\nLine exceeding 1024 characters...exiting\n");
			exit(1);
		}	
		
	   if(file_buf[len-1] == '\n')
		file_buf[len-1] = '\0';

	   myinfo* m=(myinfo*) malloc(sizeof(myinfo));
		
		
	    strncpy(m->tran,strtok(file_buf,"\t"),sizeof(m->tran));
		strncpy(t3,m->tran,sizeof(m->tran)); 
		
		if(t3[0]!='+')
		{
			if(t3[0]!='-')
			{
				printf("\nOnly + and - supported...exiting");
				exit(1);
			}
		}	
		else 
		{
		    if(t3[0]!='-')
			{
			  if(t3[0]!='+')
			  {
				printf("\nOnly + and - supported...exiting");
				exit(1);
			  }
		    }	
		}
		 strncpy(timer,strtok(NULL,"\t"),sizeof(timer));
		 m->tran_time=atoi(timer);
		 
		 time(&cur_time);
		 if((m->tran_time > cur_time) || (m->tran_time < 0))
		 {
			printf("\nWrong time present in file....exiting"); 
			exit(1); 
		  }	 
		 else if(!My402ListEmpty(dum_list))
		 {
			elem=My402ListFirst(dum_list);
			
			while((elem->next)!=&(dum_list->anchor))
			{
			  m3=((myinfo*)(elem->obj));
			
				if((m->tran_time) == (m3->tran_time))
				{
					printf("\nAlready same timestamp exists...exiting...");
					exit(1);
				}	
				elem=elem->next;
			}	
		 } 
		 
		 strncpy(m->tran_amount,strtok(NULL,"\t"),sizeof(m->tran_amount));
		 strncpy(t1,m->tran_amount,sizeof(m->tran_amount));
		if(t1[0]=='.')
			{
				printf("\nAtleast one digit before decimal should be there!!...exiting");
				exit(1);
			}
		if(t1[0]=='-')
		 {
			printf("\nAmount cannot be negative...exiting...");
			exit(1);
		 }
		 for(i=0,p=0;t1[i]!='\0';i++)
		 {
			if(t1[i]=='.')
			{
			  if(p>7)
			  {
				//printf("\nlen is %d   p is %d",strlen(t1),p);  
				//printf("\nToo high amount value...exiting...");
				//exit(1);
			  }	  
			  else if(t1[i+3]!='\0')
			  {
				printf("\nOnly 2 digits allowed after decimal...exiting...");
				exit(1);
			  }	  
			}
			else
			{
				p=p+1;
			}
		 }	 
		 

		 strncpy(t9,strtok(NULL,"\t"),sizeof(t1));
		  l2=strlen(t9);
		  if(l2==0)
		 {
			printf("\nThe description cannot be empty...exiting");
			exit(1);
		 }  
		 
		 for(i=0,j=0;i<l2;i++)
		 {
			if(!(t9[i]==' ' && t9[i+1]==' '))
			{
				t2[j]=t9[i];
				j++;
			}	
		 }
		 t2[j]='\0';
		 //printf("\nHere %s",t2); 
		 
		 strncpy(m->tran_desc,t2,sizeof(t9));
		 
		 //printf("\nHere %s",m->tran_desc);
		/* printf("\nValue %s",m->tran);
		printf("\nValue %d",m->tran_time);
		printf("\nValue %s",m->tran_amount);
		printf("\nValue %s",m->tran_desc); */
	 
	   chk=My402ListAppend(dum_list, m);
	   if(chk==0)
	   {
		 printf("\nError in appending object");  
	   }	   
	   else
		 printf("\nObject appended");   
	}
}

int file_op(My402List* dum_list,char file_name[20])
{
	FILE *fp;int i=0; int chk=0; int len=0; int k1=0; int k2=0;
	time_t cur_time;  int l2=0;
	char t1[30]; char t2[30]; int j=0; int p=0; char t3[5];char t9[30];
    memset(t1, 0, 30); memset(t2, 0, 30); memset(t3, 0, 5);memset(t9, 0, 30);
	char file_buf[1026];
    memset(file_buf, 0, 1026);
	char timer[20];
	memset(timer, 0, 20);
	My402ListElem *elem=NULL;
	myinfo* m3=(myinfo*) malloc(sizeof(myinfo));
	//printf("\nIn fn name %s ",file_name);
	fp = fopen(file_name,"r"); // read mode
			  if( fp == NULL )
			   {
				  perror("\nError while opening the tfile\n");
				  exit(1);
			   }

	while(fgets(file_buf,sizeof(file_buf),fp)!=NULL)
	{
		//memset(t1, 0, 30);  memset(t3, 0, 5);
		memset(t9, 0, 30);
		memset(t2, 0, 30);
		//memset(timer, 0, 20);
		len=strlen(file_buf);
		if(len>1024)
		{
			perror("\nLine exceeding 1024 characters...exiting\n");
			exit(1);
		}	
		
	   if(file_buf[len-1] == '\n')
		file_buf[len-1] = '\0';

	   myinfo* m=(myinfo*) malloc(sizeof(myinfo));
		
		
	    strncpy(m->tran,strtok(file_buf,"\t"),sizeof(m->tran));
		strncpy(t3,m->tran,sizeof(m->tran)); 
		
		if(t3[0]!='+')
		{
			if(t3[0]!='-')
			{
				printf("\nOnly + and - supported...exiting");
				exit(1);
			}
		}	
		else 
		{
		    if(t3[0]!='-')
			{
			  if(t3[0]!='+')
			  {
				printf("\nOnly + and - supported...exiting");
				exit(1);
			  }
		    }	
		}
		 strncpy(timer,strtok(NULL,"\t"),sizeof(timer));
		 m->tran_time=atoi(timer);
		 
		 time(&cur_time);
		 if((m->tran_time > cur_time) || (m->tran_time < 0))
		 {
			printf("\nWrong time present in file....exiting"); 
			exit(1); 
		  }	 
		 else if(!My402ListEmpty(dum_list))
		 {
			elem=My402ListFirst(dum_list);
			
			while((elem->next)!=&(dum_list->anchor))
			{
			  m3=((myinfo*)(elem->obj));
			
				if((m->tran_time) == (m3->tran_time))
				{
					printf("\nAlready same timestamp exists...exiting...");
					exit(1);
				}	
				elem=elem->next;
			}	
		 } 
		 
		 strncpy(m->tran_amount,strtok(NULL,"\t"),sizeof(m->tran_amount));
		 strncpy(t1,m->tran_amount,sizeof(m->tran_amount));
		if(t1[0]=='.')
			{
				printf("\nAtleast one digit before decimal should be there!!...exiting");
				exit(1);
			}
		if(t1[0]=='-')
		 {
			printf("\nAmount cannot be negative...exiting...");
			exit(1);
		 }
		 for(i=0,p=0;t1[i]!='\0';i++)
		 {
			if(t1[i]=='.')
			{
			  if(p>7)
			  {
				//printf("\nlen is %d   p is %d",strlen(t1),p);  
				//printf("\nToo high amount value...exiting...");
				//exit(1);
			  }	  
			  else if(t1[i+3]!='\0')
			  {
				printf("\nOnly 2 digits allowed after decimal...exiting...");
				exit(1);
			  }	  
			}
			else
			{
				p=p+1;
			}
		 }	 
		 

		 strncpy(t9,strtok(NULL,"\t"),sizeof(t1));
		  l2=strlen(t9);
		  if(l2==0)
		 {
			printf("\nThe description cannot be empty...exiting");
			exit(1);
		 }  
		 
		  //strncpy(t1,m->tran_desc,sizeof(m->tran_desc));
		 for(i=0,j=0;i<l2;i++)
		 {
			if(!(t9[i]==' ' && t9[i+1]==' '))
			{
				t2[j]=t9[i];
				j++;
			}	
		 }
		 t2[j]='\0';
		 //printf("\nHere %s",t2); 
		 
		 strncpy(m->tran_desc,t2,sizeof(t9));
		 //printf("\nHere %s",m->tran_desc);
		/* printf("\nValue %s",m->tran);
		printf("\nValue %d",m->tran_time);
		printf("\nValue %s",m->tran_amount);
		printf("\nValue %s",m->tran_desc); */
	 
	   chk=My402ListAppend(dum_list, m);
	   if(chk==0)
	   {
		 printf("\nError in appending object");  
	   }	   
	   else
		 printf("\nObject appended");   
	}
  	
	fclose(fp);	
	return TRUE;
}	

int main(int argc, char *argv[])
{
   int chk=0; int chk2=0; int chk3=0; int chk4=0;int l=0; int len=0; int k=0;int k2=0;
   My402List* list=(My402List*) malloc(sizeof(My402List));
   
   char file_name[50];
   
   if(argv[1]==NULL)
   {
	   printf("\nNo second commandline argument provided!! Format is ./warmup1 sort [tfile] exiting...");
	   exit(1);
   }
   
	   if(argc==2)
	   {
		   
		 chk=My402ListInit(list);
		  if(chk==0)
		  {
		   printf("\nError in initializing list.");
		   exit(1);
		  }   
		  printf("\nInitialized!!");
		  
		  read_file(list,stdin); 
		  
		   //display_list(list);   
		   chk2=sort_list(list);
		   if(chk2==TRUE)
			   printf("\nList sorted");
		   
		   display_list(list);
		   
		   //printf("\nEnd \n");
	   }   
	   
	   
	   k=strcmp("sort",argv[1]);
	   if(k==0 && argc==3)
	   {
		   strncpy(file_name,argv[2],sizeof(file_name));
		   l=strlen(file_name);
		   file_name[l]='\0';
		   
		   chk=My402ListInit(list);
		   if(chk==0)
		   {
			   printf("\nError in initializing list.");
			   return 0;
		   }   
		   printf("\nInitialized!!");
		   //printf("\nValue %s",file_name);
		   chk3=file_op(list,file_name);
		   
		   //display_list(list);   
		   chk4=sort_list(list);
		   if(chk4==TRUE)
			   printf("\nList sorted");
		   
		   display_list(list);
		   
		   //printf("\nEnd \n");
	   }
	
		   if(k!=0)
		   {
			  printf("\nNo sort needed so Exiting...");
			  exit(1);
		   }
 My402ListUnlinkAll(list);
 return 0;
}	
