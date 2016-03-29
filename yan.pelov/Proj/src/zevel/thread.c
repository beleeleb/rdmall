#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* print_xs(void* stam)
{
    printf("%d\n", (int)stam);
    return NULL;
}


/*struct char_print_parms
{
    char character;
    int count;
};

void* char_print(void* param)
{
    struct char_print_parms * p = (struct char_print_parms*)param;
    int i;
    
    for(i = 0; i < p->count; ++i)
    {
        fputc(p->character, stderr);
    }
    
    return NULL;
}*/

int main()
{
    pthread_t thread_id[100000];

    int i = 0;
    
    for(i = 0; i < 100000; ++i)
    {
        pthread_create(&thread_id[i], NULL, &print_xs, (void*)i);
    }

	 for(i = 0; i < 100000; ++i)
   	 {
	
	/*pthread_join(thread_id[i], NULL);*/
	pthread_detach(thread_id[i]);
	}	

	/*sleep(20);*/
    return 0;
    
    
    /*pthread_t id1, id2;
    struct char_print_parms args1;
    struct char_print_parms args2;
    
    args1.character = 'x';
    args1.count = 30000;
    pthread_create(&id1, NULL, &char_print, &args1);
    
    args2.character = 'o';
    args2.count = 20000;
    pthread_create(&id2, NULL, &char_print, &args2);
    
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);*/
    
    return 0;
}
