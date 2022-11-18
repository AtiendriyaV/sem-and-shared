#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>


void printInt(int val)
{
	char buf[6];
	int len;
	len =sprintf(buf," %d",val);
	write(1,buf,len);
}
	time_t t;

int main(int argc, char *argv[])
{
	int len,val,i=0;
	int left,right,id;
	   
	//Variable Declaration for semaphore
        int p;
	char buf[30];
        
        //variable declaration for sharedmemory
        char *b, temp[25];
	int sid,fd;
	
	// ftok to generate unique key for shared memory
	key_t key = ftok("shmfile",5);
	
        //key for semaphore
	key_t k = 100;	 //key_t k
 	struct  sembuf p1;//declaration of semaphore structure 
 	
 	id= semget(k, 1, IPC_CREAT|0777);
	if (id ==-1 )
	{
		write(1, "Refer Error", 11);
		exit(0);
	}	
	
	// id is variable declared to the int semget systemcall
	       //1 is number of semaphore to used //  
	       //checks the value of semaphore 0,1,-1//
	       // IPC_CREAT is the int flag value 
	
	   // shmget returns an identifier in id
	sid = shmget(key,1024,0666|IPC_CREAT);
	
	if (sid == -1)
	{
		write (1,"Shared memory Access Error",25);
		exit(0);
	}

	
	
	
	
	while (1)
	{
		// Entry section 
		write(1,"\n",1);		
		write(1,"=====In Entry====", 18);
		write(1,"\n",1);
		p1.sem_num=0;  /* semaphore number */
		p1.sem_op=-1;   /* semaphore operation */
		p1.sem_flg=0;  /* operation flags */
		val=semop(id,&p1,1);
		
		 //binary semaphore allocation
               int binarySemaphoreAllocation(key_t key, int semFlags)
             {
             return semget(key, 1, semFlags);
             }
 
        
		if (val == -1 )
		{
			write(1, "Wait operation Failed", 22);
			exit(0);
		}
		
		write(1,"\n",1);
		val= semctl(id,0, GETVAL, NULL);
		write(1,"Semaphore value : ",19);
		printInt(val);
		
		write(1,"\n",1);
		write(1,"In Critical section : ", 19);
		write(1,"\n",1);
		write(1,ctime(&t),15);
		write(1,"\n",1);
		 
		 
     

	//check error
	if (sid == -1)
	{
		write (1,"Shared memory Create Error",25);
		exit(0);
	}
	
	// shmat to attach to shared memory to the current process
	// void *shmat(int shmid, const void *shmaddr, int shmflg);

	b = (char*) shmat(sid,(void*)0,0);
        
        //writing the value to be displayed in semaphore
        //storing it in val and reading them 
        
	write(1,"Enter details to shared memory",20);
	
	fd=read(0,b,20);
	
	write(1,"Details updated in shared memory",20);
	
	
	
                read(0,buf,1);
		
		
		// Exit section 
		p1.sem_num=0;  /* semaphore number */
		p1.sem_op=+1;   /* semaphore operation */
		p1.sem_flg=0;  /* operation flags */
		
		write(1,"\n",1);		
		write(1,"=====In Exit====", 17);
		write(1,"\n",1);
		
		val=semop(id,&p1,1);
		
		if (val ==-1 )
		{
			write(1, "Signal operation Failed", 24);
			exit(0);
		}
		
		write(1,"\n",1);
		val= semctl(id,0, GETVAL, NULL);
		write(1,"Semaphore value : ",19);
		printInt(val);	
		
		}
		//detach from shared memory 
	//int shmdt(const void *shmaddr);
	fd = shmdt(buf);
	
	//checking error
	
	if (fd == -1)
	{
		write (1,"Shared memory Detach Error",15);
		exit(0);
	}
	return 0;

			
	        // deallocate binary semaphore, return -1 on failure
                int binarySemaphoreDeallocation(int semID)
                {
                return semctl(semID, 1, IPC_RMID);
                 }
	
	
	}
	
	 
		 
		 
	
