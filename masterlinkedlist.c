#include<stdio.h>
#include<stdlib.h>
#include <dirent.h>
 
struct score{
    double scoreNumber;
	int totalnumOfReview;	
	struct score *nextPtr;
	struct review *reviewPtr;
    
}score,*firstPtr;

struct review{
	
	int review_id;
	int length;
	char text[250];	
	int polarity;
	struct review *nextPtr;
			
}review;

FILE *inpf;

void  showList(struct score *r){	
   
    r=firstPtr;
    double scoreNumber;
    char text[250];
    int review_id;
    
    if(r==NULL){
    return;
    }
    
    while(r!=NULL){
    printf("Score:%f\n ",r->scoreNumber);
    printf("Review id:%d\n ",r->reviewPtr->review_id);
    printf("Text:%s\n ",r->reviewPtr->text);
    printf("Number of words:%d\n ",r->reviewPtr->length);
    printf("Polarity:%d\n\n\n ",r->reviewPtr->polarity);
    r=r->nextPtr;
    }

}

void addScore(double scoreNumber, int review_id, int length, char text[], int polarity, int totalnumOfReview){

	struct score *newNode;
	struct score *currentPtr;
	struct score *prev;
	
	struct review *newNode1;
	struct review *currentPtr1;
	struct review *prev1;

	// create node to insert and assign values to its fields
	newNode=(struct score *)malloc(sizeof(score));
	newNode->reviewPtr=(struct review *)malloc(sizeof(review));
	newNode->scoreNumber=scoreNumber;
	newNode->totalnumOfReview=totalnumOfReview;	
	newNode->reviewPtr->review_id=review_id;
	newNode->reviewPtr->length=length;
	strcpy(newNode->reviewPtr->text,text);
	newNode->reviewPtr->polarity=polarity;
	newNode->nextPtr=NULL;

	// if LL empty
	if (firstPtr == NULL) 
		firstPtr=newNode;
	// if LL not empty
	else {
		currentPtr=firstPtr;
		while (currentPtr != NULL && currentPtr->scoreNumber<newNode->scoreNumber) {
			prev=currentPtr;
			currentPtr=currentPtr->nextPtr;
			totalnumOfReview++;			
		}

		
		// insert node in a sorted fashion
		if (currentPtr!=NULL)
			newNode->nextPtr=currentPtr;

		// if value to insert is the leat in LL then have header point to node
		if (currentPtr==firstPtr)
			firstPtr=newNode;
		// otherwise insert node in correct position
		else 
			prev->nextPtr=newNode;

	}
       
}


void calculateAverageScore(){
	
    struct score *n;
    double averageScore,total,scoreNumber;
    int count;
    
	n = firstPtr;

    while ( n != NULL){
    total += n->scoreNumber;
    count++;
    n=n->nextPtr;
    }
    
    averageScore=total/(double)count;
    printf("%f", averageScore);
  	
}

listReviewsInASpecificPolarity(int polarity){
	
	struct score *currP;
	
	currP=firstPtr;
	printf("Review id's list in a specific polarity:\n");
	while(currP!=NULL){
		
		while(currP->reviewPtr->polarity==polarity){
		printf("%d\n",currP->reviewPtr->review_id);
		currP=currP->nextPtr;
		}

		currP=currP->nextPtr;

	}
}

void listReviewsContainsAParticularWord(char word[]){
	
    struct score *np;  
    np=firstPtr;
    
    printf("Review id's list contains a particular word:\n");
    while(np != NULL){
        if((strstr(np->reviewPtr->text,word)) != NULL){
            printf("%d\n",np->reviewPtr->review_id);
        }
        np=np->nextPtr;
    }

}


void removeReviewsBetweenAspecificScope(double starting_scope_period,double end_scope_period){
	
	struct score *currP, *prevP;
    prevP = NULL;

    for (currP= firstPtr ; currP!=NULL ; prevP=currP, currP=currP->nextPtr) {

    if (currP->scoreNumber == starting_scope_period) {
    	     
    while( currP->scoreNumber != end_scope_period ){
	  	
      if (prevP == NULL) {
      firstPtr = currP->nextPtr;
      }
	       
	  else{
      prevP->nextPtr = currP->nextPtr;
      }
            
      free(currP); 
	  currP=currP->nextPtr;     
     }
      
    }
  }
}


int  main(){
	
    int i;
    double scoreNumber,starting_scope_period,end_scope_period;
    int totalnumOfReview,review_id,length,polarity,totalScore;
    char text[250];
    char word[20];
    char a[1];
    char *txt;

    struct score *n;
    struct score *nwP;
    struct score *currentPtr;

    firstPtr=NULL;
    
    DIR *dir;
    struct dirent *ent;

		  
	if ((dir = opendir ("C:\\ReviewsAboutVideoAndTelevisions\\home\\std\\ReviewsAboutVideoAndTelevisions")) != NULL) {
    /* print all the files and directories within directory */
        
    while ((ent = readdir (dir)) != NULL) {
        
    	//Cyle empty two times
		char str1[4],str2[4];
    	int ret1,ret2;
    	strcpy(str1, ".");
        strcpy(str2, "..");
        
        ret1 = strcmp(str1, ent->d_name);
        ret2 = strcmp(str2, ent->d_name);
                
        if(ret1 == 0){
         continue;
        }
        if(ret2 == 0){
         continue;
        }
    	
	    //Get filenames in order to read files
		char locfile[]="C:\\ReviewsAboutVideoAndTelevisions\\home\\std\\ReviewsAboutVideoAndTelevisions";
        strcat(locfile,ent->d_name);

        //Reading txt files
        
        char *pros="Pros";
        char *cons="Cons";
        //int count;
        char *s;
        //count=0;

	    if((inpf = fopen(locfile,"r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
		return;
	    }	    
	    
        memset(text,0,sizeof(text));
		fread(&text, sizeof(text), 8, inpf);
		
		
		if(strstr(text,pros)&&strstr(text,cons)){
		    polarity=0;	
		}
		else if(strstr(text,cons)){
			polarity=-1;
		}
		else{			
			polarity=1;
		}

		
		fclose(inpf);
		
		//Counting length
	    FILE *inpf2;
        int count = 1;
        char c;
        inpf2 = fopen(locfile, "r");
        if(inpf2 == NULL)
        printf("file not found\n");
        while((c = fgetc(inpf2)) != EOF) {
        if(c == ' ')
           count++;
        }
        
        length=count+1;
        
        fclose(inpf2);
    
        //Get score and review id from filename
        char *remainderPtr;    
        scoreNumber = strtod (ent->d_name , &remainderPtr );
		
		char *reviewchr;
		reviewchr = ent->d_name;
		memmove (ent->d_name, ent->d_name+1, strlen (ent->d_name+1));					
		review_id = strtoul(remainderPtr , &reviewchr ,0 );
		
		addScore(scoreNumber, review_id, length, text, polarity, totalnumOfReview);


        totalnumOfReview++;
        	    	    

    }    
    
    closedir (dir);
   
  
    }
	      

    else {
     /*could not open directory */
    printf("could not open directory"); 

    }

   
    while(1){
    	
    printf("\n     Welcome \n");
    printf("===============\n");
    printf("\n1.Display list\n");
    printf("2.Add a new review-score and a new review into a review-score\n");
    printf("3.Calculate the average score of all the reviews\n");
    printf("4.Show the review id s and the total number of them in a specific polarity\n");
    printf("5.List the id s of reviews which have a particular word\n");
    printf("6.Remove the reviews between in a specific score-scope\n");
    printf("7.Exit\n");
    printf("Enter your choice : ");
    
    if(scanf("%d",&i)<=0){
        printf("Enter only an Integer\n");
        exit(0);
    }
    
	else {
		
        switch(i){
        case 1:      
	    if(firstPtr==NULL){
        printf("List is Empty\n");
        }
        else{
        printf("Element(s) in the list are :\n ");
        }
        showList(n);
        break;
        
        case 2:
       	printf("Enter the score to insert : ");
        scanf("%lf",&scoreNumber);
        if(scoreNumber>=0 && scoreNumber<=5){
        printf("Enter the review id to insert : ");
        scanf("%d",&review_id);
        
        currentPtr=firstPtr;
        while(currentPtr!=NULL){
			if (currentPtr->reviewPtr->review_id==review_id) {
			printf("Existent review id.Please enter the different id:\n");
			printf("Enter the review id to insert : ");
            scanf("%d",&review_id);
            }
		currentPtr=currentPtr->nextPtr;	
        }
        
        char emp[1];
        char pros1[]="Pros";
        char cons1[]="Cons";
		printf("Enter the text to insert : ");
		gets(emp);
		gets(text);
        
        //Count polarity
		if(strstr(text,pros1)&&strstr(text,cons1)){
		    polarity=0;	
		}
		else if(strstr(text,cons1)){
			polarity=-1;
		}
		else if(strstr(text,pros1)){			
			polarity=1;
		}
		else{
			polarity=9;
		}
        
        //Count length
        int numWord = 0, i;
		for (i = 0;text[i] != '\0';i++){
        if (text[i] == ' ')
            numWord++;    
        }
        length=numWord+1;
        
        addScore(scoreNumber, review_id, length, text, polarity, totalnumOfReview);	
        }
		else{
		printf("Invalid score");	
		}       		                              
        break;

        case 3:
        calculateAverageScore();
        break;
        
        case 4:
        printf("Enter the polarity(+1,0,-1) : ");
        scanf("%d",&polarity);
        listReviewsInASpecificPolarity(polarity);
        break;
        
        case 5:
        printf("Enter the keyword : ");
        scanf("%s",word);
       	listReviewsContainsAParticularWord(word);        
        break;
        
        case 6:
        if(firstPtr==NULL)
        printf("List is Empty\n");
        else{      
        printf("Enter the first score to delete : ");
        scanf("%lf",&starting_scope_period);
        printf("Enter the last score to delete : ");
        scanf("%lf",&end_scope_period);
        
        nwP=firstPtr;
        while(nwP!=NULL && nwP->scoreNumber!=starting_scope_period){
		nwP=nwP->nextPtr;	
        }
        
       
        if(starting_scope_period<0||starting_scope_period>5||end_scope_period<0||end_scope_period>5||starting_scope_period>end_scope_period){
        	printf("Invalid input");
        }
        
        else{
        removeReviewsBetweenAspecificScope(starting_scope_period, end_scope_period);	
        }
        	 
		}       
        break;
        
        case 7:     
		return 0;
        default:    
		printf("Invalid option\n");
        }
    }
    }
    return 0;
    
}




