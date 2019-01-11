#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 50
#define MAX_CODE 10
#define MAX_RECORDS 20
#define MAX_SUBJECTS 5

typedef struct student_record_node{
	int rollno;
	int marks;
	char name[MAX_NAME];
	char subject[MAX_CODE];
	struct student_record_node *next;

}student_record;

void display(student_record *lptr);
void MergeSort(student_record** headRef);
student_record* mergeself(student_record* a, student_record* b);
void divide(student_record* source, student_record** frontRef, student_record** backRef);

/*----------------------------------------------------------------------------------------------------------------------------*/
// Function to create database using linked list

student_record* createlist(student_record* list_ptr)
{
	int roll_no, mrks;
	char stu_name[MAX_NAME], sub_code[MAX_CODE];
	student_record *nptr;
	
	
	list_ptr = NULL; int proceed=1;
	printf("Do You want to create List? (1/0): ");
	
	scanf("%d",&proceed);
	while(proceed == 1)
	{
		printf("\n");
		printf("Enter the Name of Student: ");
		scanf("%s",stu_name);
		printf("Enter the Roll No.: ");
		scanf("%d",&roll_no);
		printf("Enter the Subject Code: ");
		scanf("%s",sub_code);
		printf("Enter the Marks: ");
		scanf("%d",&mrks);
	
		nptr = (student_record*)malloc(sizeof(student_record));
		strcpy(nptr -> name , stu_name);
		nptr -> rollno = roll_no;
		strcpy(nptr -> subject , sub_code);
		nptr -> marks = mrks;
		
		if(list_ptr == NULL)
		{
			list_ptr=nptr;
		}
		else
		{	
			nptr -> next = list_ptr;
			list_ptr = nptr;	
		}
		printf("Do you want to add another student (1/0): ");
		
		scanf("%d",&proceed);
	}
	MergeSort(&list_ptr);
	return(list_ptr);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to insert or update the list
/*
student_record* insertnode(student_record *lptr)
{
	int roll_no,mrks,flag;
	char sub_code[MAX_CODE], stu_name[MAX_NAME];
	student_record *nptr;
	student_record *ptr, *prev;
	
	ptr = lptr;
	
	printf("Enter the Roll No.: ");
	scanf("%d",&roll_no);
	printf("Enter the Subject Code: ");
	scanf("%s",sub_code);
	
	while(lptr != NULL && lptr -> next != NULL && flag == 0)
	{
		if(lptr->rollno == roll_no && strcmp(lptr->subject,sub_code)==0)
		{
			printf("Enter the Name of Student: ");
			scanf("%s",stu_name);
			printf("Enter the marks: ");
			scanf("%d",&mrks);
			
			strcpy(lptr->name,stu_name);
			lptr -> marks = mrks;
			printf("List Updated...\n");
			flag = 1;
		}
		else
		{
			lptr = lptr -> next;
		}
	}	
	
	lptr = ptr;
		
	if(flag != 1)
	{
		while(roll_no <= lptr->rollno)
		{
			lptr = lptr -> next;
		}
			
		printf("Enter the Name of Student: ");
		scanf("%s",stu_name);
		printf("Enter the marks: ");
		scanf("%d",&mrks);
			
		nptr = (student_record*)malloc(sizeof(student_record));
		nptr -> rollno = roll_no;
		nptr -> marks = mrks;
		strcpy(nptr -> name, stu_name);
		strcpy(nptr -> subject, sub_code);
			
		nptr -> next = lptr -> next;
		lptr -> next = nptr;
			
		printf("\nInsertion Successful !!\n");
	}
	return(ptr);	
}
*/
student_record* insertnode(student_record *lptr)
{
	int roll_no,mrks,flag=0;
	char sub_code[MAX_CODE], stu_name[MAX_NAME];
	student_record *nptr, *ptr;
	ptr = lptr;
	
	printf("Enter the Roll No.: ");
	scanf("%d",&roll_no);
	printf("Enter the Subject Code: ");
	scanf("%s",sub_code);
	printf("Enter the Name of Student: ");
	scanf("%s",stu_name);
	printf("Enter the Marks: ");
	scanf("%d",&mrks);
	
	while(lptr != NULL && flag == 0)
	{
		if(lptr->rollno == roll_no && strcmp(lptr->subject, sub_code) == 0)
		{
			strcpy(lptr->name, stu_name);
			lptr->rollno = roll_no;
			strcpy(lptr->subject, sub_code);
			lptr->marks = mrks;
			printf("List Updated Successfully.\n");
			flag = 1;
		}
		else
		{
			lptr = lptr -> next;
			
		}
	}
	lptr = ptr;
	if(flag == 0)
	{
		nptr = (student_record*)malloc(sizeof(student_record));
		nptr -> rollno = roll_no;
		nptr -> marks = mrks;
		strcpy(nptr -> name, stu_name);
		strcpy(nptr -> subject, sub_code);
		
		nptr -> next = lptr;
		lptr = nptr;
	}
	MergeSort(&lptr);
	return(lptr);
}
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to delete a record

student_record* deletenode(student_record *lptr)
{
	int roll_no, flag = 0;
	char sub_code[MAX_CODE];
	student_record *nptr;
	student_record *prev, *ptr;
	
	printf("Enter the Roll no.: ");
	scanf("%d",&roll_no);
	printf("Enter Subject Code: ");
	scanf("%s",sub_code);
	
	ptr = lptr;
	prev = lptr;
	
	if(lptr == NULL)
	{
		printf("NO List\n");
	}
	else
	{
		while(lptr->next != NULL && flag == 0)
		{
			if(roll_no == lptr->rollno && strcmp(sub_code, lptr->subject)==0)
			{
				if(prev == lptr)
				{
					lptr = lptr -> next;
					free(prev);
				}
				else
				{
					nptr = lptr;
					lptr = lptr -> next;
					prev -> next = lptr;
					free(nptr);
				}
			
				flag = 1;
				printf("Record Successfully Deleted.\n");
			}
			else
			{
				prev = lptr;
				lptr = lptr -> next;
			}
		}
		if(flag == 0)
		{
			printf("Record doesn't Exist or Incorrect Details are provided.\n");
		}
	}
	
	return(ptr);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to get number of records

int numnodes(student_record *lptr)
{
	int count = 0;
	student_record *nptr;
	
	nptr = lptr;
	
	if(nptr == NULL)
	{
		printf("NO list\n");
	}
	else
	{
		while(nptr != NULL)
		{
			count++;
			nptr = nptr -> next;
		}
	}
	
	return(count);
}
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to check if the list is empty or not

void islistempty(student_record *lptr)
{
	if(lptr == NULL)
	{
		printf("List is Empty.\n");
	}
	else
	{
		printf("List is not Empty.\n");
	}
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to check if the list is full

void islistfull(int no_of_records)
{
	if(no_of_records == MAX_RECORDS)
	{
		printf("List is Full\n");
	}
	else
	{
		printf("List is Not Full\n");
	}
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to Get Maximum Marks

void getMaxmarks(student_record *lptr, char sub_code[])
{
	student_record *nptr;
	int max, roll_no;
	
	nptr = lptr;
	max = 0;
	
	while(lptr != NULL)
	{
		if(strcmp(sub_code, lptr->subject)==0)
		{
			if(lptr->marks > max)
			{
				max = lptr -> marks;
				roll_no = lptr -> rollno;
			}
			else
			{lptr = lptr -> next;}
		}
		else
		{lptr = lptr -> next;}
	}
	printf("Maximum marks scored in %s are %d by Roll No. %d\n", sub_code, max, roll_no);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to find topper

void topper(student_record *lptr)
{
	int flag = 0, max = 0, total = 0;
	student_record *nptr, *ptr;

	while(flag != 1)
	{
		nptr = lptr -> next;
		total = lptr -> marks;
		
		while(lptr->rollno == nptr->rollno)
		{
			total = total + nptr->marks;
			nptr = nptr -> next;
		}
		if(total > max)
		{
			max = total;
			ptr = lptr;
		}
		lptr = lptr -> next;
		if(nptr->next == NULL)
		{
			flag = 1;
		}
	}
	printf("Topper is %s with %d marks in all\n", ptr->name,max);
}

/*
student_record* topper(student_record *lptr)
{
	student_record *ptr, *tptr=NULL;
	student_record *rptr, *rprev, *tprev;
	rptr = lptr;
	int roll;
	int max_marks = -1;
	int marks;
	while(rptr!=NULL)
	{
		roll = rptr->rollno;
		marks = 0;
		while(rptr->rollno == roll)
		{
			marks = marks+rptr->marks;
			rprev = rptr;
			rptr = rptr->next;
		}
		if(marks>max_marks)
		{
			while(tptr!=NULL)
			{
				tprev = tptr;
				tptr = tptr->next;
				free(tprev);
			}
			free(tprev);
		}
		if(marks == max_marks)
		{
			ptr = (student_record*)malloc(sizeof(student_record));
			strcpy(ptr->name,rprev->name);
			ptr->rollno = rprev->rollno;
			strcpy(ptr->subject,rprev->subject);
			ptr->marks = rprev->marks;
			
			ptr->next = tptr;
			tptr = ptr;
		}
	}
	return(tptr);
}*/

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to find failures

void failures(student_record *lptr)
{
	student_record *nptr, *list;
	int cutoff, count = 0;
	char sub_code[MAX_CODE];
	list = NULL;
	
	printf("Enter the Subject Code for which you want to find failures: ");
	scanf("%s",sub_code);
	printf("Enter the cuttoff Marks");
	scanf("%d",&cutoff);
	
	while(lptr != NULL)
	{
		if(strcmp(lptr -> subject, sub_code) == 0)
		{
			if(lptr->marks < cutoff)
			{
				nptr = (student_record*)malloc(sizeof(student_record));
				nptr -> rollno = lptr -> rollno;
				strcpy(nptr->name, lptr->name);
				strcpy(nptr->subject, sub_code);
				nptr -> marks = lptr -> marks;
				count++;
				
				nptr -> next = list;
				list = nptr;
			}
		}
		lptr = lptr -> next;
	}
	if(count == 0)
	{
		printf("All have passed.");
	}
	display(list);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to find Kth popular subject

void kth_popular(student_record *lptr)
{

}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to delete Duplicate Entries (UNIQUE)

void unique(student_record *lptr)
{
	int count=0;
	student_record *nptr, *prev;
	
	while(lptr->next != NULL)
	{
		nptr = lptr -> next;
		prev = lptr;
		while(nptr != NULL)
		{
			if(lptr->rollno == nptr->rollno && strcmp(lptr->subject, nptr->subject) == 0)
			{
				count++;
				prev -> next = nptr -> next;
				free(nptr);
			}
			nptr = nptr -> next;
			prev = prev -> next;
		}
		lptr = lptr -> next;
	}
	printf("Deleted %d Duplicate Entries Successfully\n", count);
}
/*
void unique(student_record *lptr)
{
	student_record *prev, *nptr, *ptr;
	ptr = lptr;
	prev = lptr;
	if(lptr == NULL)
	{printf("No list.\n");}
	else
	{
		while(lptr->next != NULL)
		{
			prev = lptr;
			lptr = lptr -> next;
			if(lptr->rollno == prev->rollno && strcmp(lptr->subject, prev->subject) == 0)
			{
				prev -> next = lptr -> next;
				nptr = lptr;
				lptr = prev;
				free(nptr);
			}
			lptr = lptr -> next;
		}
	}
	
}*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to find UNION of two lists

student_record* union_list(student_record *list_1, student_record *list_2)
{
	student_record *list_3;
	student_record *nptr;
	int count = 0;
	list_3 = NULL;
	
	while(list_1 != NULL)
	{
		nptr = (student_record*)malloc(sizeof(student_record));
		strcpy(nptr->name, list_1->name);
		nptr->rollno = list_1->rollno;
		strcpy(nptr->subject, list_1->subject);
		nptr->marks = list_1->marks;
		count++;
		
		nptr -> next = list_3;
		list_3 = nptr;
		list_1 = list_1 -> next;
		
	}
	
	while(list_2 != NULL)
	{
		nptr = (student_record*)malloc(sizeof(student_record));
		strcpy(nptr->name, list_2->name);
		nptr->rollno = list_2->rollno;
		strcpy(nptr->subject, list_2->subject);
		nptr->marks = list_2->marks;
		count++;
		
		nptr -> next = list_3;
		list_3 = nptr;
		list_2 = list_2 -> next;
		
	}
	unique(list_3);
	return(list_3);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to find the INTERSECTION of 2 lists

student_record* intersection_list(student_record *list_1, student_record *list_2)
{
	student_record *list_3, *nptr, *ptr;
	int count = 0;
	list_3 = NULL;
	
	ptr = list_2;
	while(list_1 != NULL)
	{
		list_2 = ptr;
		while(list_2 != NULL)
		{
			if(list_1->rollno == list_2->rollno && strcmp(list_1->subject, list_2->subject) == 0)
			{
				nptr = (student_record*)malloc(sizeof(student_record));
				strcpy(nptr->name, list_1->name);
				nptr -> rollno = list_1 -> rollno;
				strcpy(nptr->subject, list_1->subject);
				nptr -> marks = list_1 -> marks;
				count++;
				
				nptr -> next = list_3;
				list_3 = nptr;
			}
			list_2 = list_2 ->next;
		}
		list_1 = list_1 -> next;
	}
	return(list_3);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function for finding DIFFERENCE in 2 lists
/*
student_record* difference(student_record *list_1, student_record *list_2)
{
	int count = 0, flag = 0;
	student_record *list_3, *ptr, *nptr;
	list_3 = NULL;
	ptr = list_2;
	
	while(list_1 != NULL)
	{
		list_2 = ptr;
		while(list_2 != NULL && flag == 0)
		{
			if(list_1->rollno == list_2->rollno && strcmp(list_1->subject, list_2->subject) == 0)
			{
				flag = 1;
			}
			list_2 = list_2 -> next;
		}
		if(flag != 1)
		{
			nptr = (student_record*)malloc(sizeof(student_record));
			strcpy(nptr->name, list_1->name);
			nptr -> rollno = list_1 -> rollno;
			strcpy(nptr->subject, list_1->subject);
			nptr -> marks = list_1 -> marks;
			count++;
			
			nptr -> next = list_3;
			list_3 = nptr;
		}
		list_1 = list_1 -> next;
	}
	return(list_3);
}
*/

student_record* difference(student_record *list_1, student_record *list_2)
{
	int flag = 0, count=0;
	student_record *list_3, *nptr;
	list_3 = NULL;
	
	while(list_1 != NULL)
	{
		flag = 0;
		while(list_2 != NULL && flag == 0)
		{
			if(list_1->rollno == list_2->rollno && strcmp(list_1->subject, list_2->subject) == 0)
			{
				flag = 1;
			}
			list_2 = list_2 -> next;
			if(flag == 0)
			{
				nptr = (student_record*)malloc(sizeof(student_record));
				strcpy(nptr->name, list_1->name);
				nptr -> rollno = list_1 -> rollno;
				strcpy(nptr->subject, list_1->subject);
				nptr -> marks = list_1 -> marks;
				count++;
			
				nptr -> next = list_3;
				list_3 = nptr;
			}
		}
		list_1 = list_1 -> next;
	}
	return(list_3);
}


/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function for SYMMETRIC DIFFERENCE of 2 lists

student_record* symmetric_diff(student_record *list_1, student_record *list_2)
{
	student_record *list_3, *ptr1, *ptr2;
	int count = 0;
	list_3 = NULL;
	
	ptr1 = difference(list_1, list_2);
	ptr2 = difference(list_2, list_1);
	list_3 = union_list(ptr1, ptr2);
	return(list_3);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function to display records

void display(student_record *lptr)
{
	student_record *nptr;
	nptr = lptr;
	if(nptr == NULL)
	{
		printf("\nNo list to Display.\n");
	}
	while(nptr != NULL)
	{
		printf("\n-----------------------------------------\n");
		printf("Name of Student: %s\n", nptr->name);
		printf("Roll Number: %d\n", nptr->rollno);
		printf("Subject Code: %s\n", nptr->subject);
		printf("Marks: %d\n", nptr->marks);
		printf("\n-----------------------------------------\n");
		nptr = nptr -> next;
	}
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Function for MERGE SORT

void MergeSort(student_record** headRef)
{
	student_record* head =* headRef;
	student_record* a;
	student_record* b;
 
  
	if ((head == NULL) || (head->next == NULL))
	{
		return ;
	}
	
	divide(head, &a, &b); 
	MergeSort(&a);
	MergeSort(&b);
   
	*headRef = mergeself(a, b);
}
		
void divide(student_record* source, student_record** frontRef, student_record** backRef)
{
	student_record* fast;
	student_record* slow;
	
	if (source==NULL || source->next==NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
  
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
 
  
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}
 
student_record* mergeself(student_record* a, student_record* b){
	student_record* result = NULL;
 
  
	if (a == NULL)
	return(b);
	else if (b==NULL)
	return(a);
 
	if (a->rollno < b->rollno)
	{
		result = a;
		result->next = mergeself(a->next, b);
	}
	else
	{
		result = b;
		result->next = mergeself(a, b->next);
	}
	return(result);
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
// Main Function

int main()
{
	int n, choice;
	int no_of_records;
	student_record *lptr;
	student_record *list1, *list2, *list3;
	char proceed = 'y';
	char sub_code[MAX_CODE];
	
	lptr = NULL;
	list1 = NULL; list2 = NULL; list3 = NULL;
	
	printf("\nSTUDENT RECORDS\n");
	
	lptr = createlist(lptr);
	
	while(proceed != 'n' || proceed != 'N')
	{
		printf("\nSelect an option you want to perform on database:\n");
		printf("1. Insert or Update\n");
		printf("2. Delete\n");
		printf("3. Get number of records\n");
		printf("4. Check the list if it is empty\n");
		printf("5. Check the list if it is full\n");
		printf("6. Get maximum marks in a subject\n");
		printf("7. Find Topper\n");
		printf("8. Find Failure\n");
		printf("9. Find Kth popular subject\n");
		printf("10. List Unique\n");
		printf("11. List Union\n");
		printf("12. List Intersection\n");
		printf("13. List Difference\n");
		printf("14. List Symmetric Difference\n");
		printf("15. Display List\n");
		
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1 : printf("Enter the required details as asked\n");
					 lptr = insertnode(lptr);
					 break;
					 
			case 2 : printf("Enter the required details\n");
					 lptr = deletenode(lptr);
					 break;
					 
			case 3 : printf("Getting No. of Records...\n");
					 no_of_records = numnodes(lptr);
					 printf("Total Number of Records is %d\n", no_of_records);
					 break;
					 
			case 4 : printf("Checking...\n");
					 islistempty(lptr);
					 break;
					 
			case 5 : printf("Checking...\n");
					 islistfull(no_of_records);
					 break;
					 
			case 6 : printf("Enter the Subject Code of Subject whose\nmaximum marks you want: ");
					 scanf("%s",sub_code);
					 getMaxmarks(lptr, sub_code);
					 break;
					 
			case 7 : topper(lptr);
					 break;
					 
			case 8 : failures(lptr);
					 break;
			
			case 9 : kth_popular(lptr);
					 break;
					 
			case 10 : printf("Deleting Duplicates...\n");		 
					  unique(lptr);
					  break;
					  
			case 11 : printf("For Finding Union, Please Enter the data into 2 lists\n");
					  printf("Enter the data for the first list:\n");
					  list1 = createlist(list1);
					  
					  printf("\nEnter the data for the second list:\n");
					  list2 = createlist(list2);
					  
					  list3 = union_list(list1, list2);
					  display(list3);
					  break;
					  
			case 12 : printf("For finding Intersection, Please Enter the data into 2 lists\n");
					  printf("Enter the data for the first list:\n");
					  list1 = createlist(list1);
					  
					  printf("\nEnter the data for the second list:\n");
					  list2 = createlist(list2);
					  
					  list3 = intersection_list(list1, list2);
					  display(list3);
					  break; 
					  
			case 13 : printf("DIFFERENCE\n");
					  printf("Enter the data for first list:\n");
					  list1 = createlist(list1);
					 
					  printf("\nEnter the data for the second list:\n");
					  list2 = createlist(list2);
					 
					  list3 = difference(list1, list2);
					  display(list3);
					  break;
					 
			case 14 : printf("SYMMETRIC DIFFERENCE\n");
					  printf("Enter the data for the first list:\n");
					  list1 = createlist(list1);
					  
					  printf("\nEnter the data for the second list:\n");
					  list2 = createlist(list2);
					  
					  list3 = symmetric_diff(list1, list2);
					  display(list3);
					  break;
					 
			case 15 : display(lptr);
					  break;
					  
			default : printf("Invalid Choice...\n");
					  break;		   
		}
	
		printf("Do you want to proceed (Y/N): ");
		getchar();
		scanf("%c",&proceed);
	}

	return(0);
}





