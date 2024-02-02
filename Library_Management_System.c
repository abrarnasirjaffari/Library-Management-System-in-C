#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
// declaring the file pointers
FILE *fp;
FILE *student;
FILE *pwdcheck;
FILE *studentinfo;
// declaring the structures required
struct bookInfo{
    int bookId;
    char bookName[50];
    char authorName[50];
}a;
struct studentInfo{
    int id;
    char studentName[50];
    char bookName[50];
    int studentId;
}s,d;
struct studentsignup{
	int id;
	char studentname[50];
	char password[50];
}c;
void addBook(){
	// function to add book
    fp=fopen("books.txt","ab");
    
    while(1){
	// taking book id from the admin
    printf("Enter book id: ");
    scanf(" %d", &a.bookId);
    if(a.bookId<=0){
    printf("Invalid id\n");
    continue;
	}
	else{
		break;
	}
	}
	// taking book name from the admin
    printf("Enter book name: ");
    fflush(stdin);
    gets(a.bookName);
	// taking author name from the admin
    printf("Enter author name: ");
    fflush(stdin);
    gets(a.authorName);
	system("cls");
    printf("Book Added Successfully\n");
	printf("press any key to continue...\n");
	getch();

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);


}
void delBook(){
    int id,f=0;
	// function to delete book
	// taking id of the book to delete
    printf("Enter the id of the book to remove:");
    scanf(" %d",&id);
    FILE *pf;
    fp=fopen("books.txt","rb");
    pf=fopen("temp.txt","wb");
    while (fread(&a,sizeof(a),1,fp)==1)
    {
        if(id==a.bookId){
            f=1;
        }
        else{
            fwrite(&a,sizeof(a),1,pf);
        }
    }
        if(f==1){
            printf("Book deleted successfully\n");
            getch();
        }
        else{
            printf("Record not found\n");
            printf("Enter any key to continue...\n");
			getch();
        }
        // closing the files
        fclose(fp);
        fclose(pf);

		// removing the file and renaming the temp file
        remove("books.txt");
        rename("temp.txt", "books.txt");
}
void bookList(){
	// printing the available books
    printf("Available books\n");
    printf("%-10s %-30s %-30s\n","book Id","book Name","author Name");
    fp=fopen("books.txt","rb");
    while (fread(&a,sizeof(a),1,fp)==1)
    {
        printf("%-10d %-30s %-30s\n",a.bookId,a.bookName,a.authorName);
    }
    fclose(fp);
}
void issuebook(){
	// function for issuing books
    int m=0;
    printf("Enter the id of the book you want to issue:");
    scanf(" %d",&s.id);

    fp=fopen("books.txt","rb");
    while (fread(&a,sizeof(a),1,fp))
    {
    if(s.id==a.bookId){
        m=1;
		// copying one string into another
        strcpy(s.bookName,a.bookName);
        break;
    }
    }
    if (m==0)
    {
        printf("No book found with the given id\n");
        getch();
    }
    else{
    student=fopen("issuedbooks.txt","ab");
	// taking inputs from the user
    while(1){
    printf("Enter student id :\n");
    scanf(" %d",&s.studentId);
    if(s.studentId<=0){
    	printf("Invalid id\n");
    	continue;
	}
	else{
		break;
	}
	}
   
    fflush(stdin);
	//taking name from the user 
    printf("Enter student name :\n");
    gets(s.studentName);
    printf("Book issued successfully\n");
    fwrite(&s,sizeof(s),1,student);
    fclose(student);
    printf("Press any key to continue\n");
    getch();

    }
    
}
void IssuedbookList(){
	// function to see the list of issued books
    system("cls");
    printf("%-30s %-30s %-30s\n","Student Id","Student name","Book name");
    student=fopen("issuedbooks.txt","rb");
    while(fread(&s,sizeof(s),1,student)==1){
    printf("%-30d %-30s %-30s\n",s.studentId,s.studentName,s.bookName);
    }
    fclose(student);
    getch();
}

int main(){
	// declaring the variables required
	char choice;
	int choice2;
	int choice3;
	int choice4;
	int studentId;
	int id;
	char password[50];
	char name[50];
	char pwd[50];
	char inputpwd[30];
	printf("\n\t\t\t---------------Welcome to library management system---------------\t\t\t\n\n");
	printf("Are you admin or student?(press 'a' or 'A' for admin and 's' or 'S' for student)\n");
	scanf(" %c",&choice);
	 if (choice=='a' || choice=='A'){
	 	printf("Enter the password : \n");
	 	scanf(" %s",&inputpwd);
	 	pwdcheck=fopen("pwd.txt","r");
	 	while(!feof(pwdcheck)){
	 		fgets(pwd,50,pwdcheck);
			// checking the password
	 		if(!strcmp(pwd,inputpwd)){
	 			printf("Login successful\n");
				printf("Enter any key to continue...\n");
				fclose(pwdcheck);
				getch();
				while (1)
        {
        system("cls");
        printf("1.Add book\n");
        printf("2.Remove book\n");
        printf("3.Issued books list\n");
        printf("0.exit\n");
        printf("Enter your choice : \n");
        scanf(" %d",&choice2);
        if(choice2==1){
			// calling the addbook function
            addBook();
        }
        else if (choice2==2)
        {
			// calling the delete book function
            delBook();
        }
        else if(choice2==3){
			// calling the function to see the list of issued books
            IssuedbookList();
        }
        else if(choice2==0){
            exit(0);
        }
        else{
            printf("Enter valid choice\n");
        }
        }	
			 }
			 else{
			 	printf("Wrong password\n");
			 }
		 }
	 }
	 else if (choice=='s' || choice=='S')
	 {	
		while (1)
		{
		// asking user for the choice
		printf("1.Login\n");
		printf("2.Signup\n");
		printf("0.exit\n");
		printf("Enter your choice:\n");
		scanf(" %d",&choice3);
		if (choice3==1)
		{
			printf("Enter your id\n");
			scanf(" %d",&id);
			fflush(stdin);
			studentinfo=fopen("Studentinfo.txt","rb");
			while (fread(&c,sizeof(c),1,studentinfo)==1)
			{
				if (c.id==id)
				{	
					//  asking password from the user
					printf("Enter your password\n");
					fflush(stdin);
					gets(password);
					if (!strcmp(password,c.password))
					{
					
						printf("Login successful\n");
						printf("Press any key to continue...\n");
						getch();
						while(1){
						system("cls");
						printf("Enter your choice:\n");
						printf("1.Book List\n");
   						printf("2.Issue Book\n");
    					printf("0.exit\n");
						fflush(stdin);
						scanf(" %d",&choice4);
						if(choice4==1){
    					system("cls");
    					bookList();  
						getch();
						system("cls");
						}
						else if(choice4==2){
							system("cls");
							// calling the issue book function
							issuebook();	
							}
						else if(choice4==0){
							system("cls");
							exit(0);
							}
						else{
								printf("invalid choice\n");
							}
					}
						}
					
					else{
						printf("Incorrect password\n");
					}	
				}
				else{
					printf("Invalid Id!user with this Id does not exist\n");
					getch();
					system("cls");
				}
			}
		}
		else if (choice3==2)
		{	
			// taking inputs from the user
			printf("Enter your Student Id:\n");
			scanf(" %d",&c.id);
			studentinfo=fopen("Studentinfo.txt","wb");
			printf("Enter your Name:\n");
			fflush(stdin);
			gets(c.studentname);
			fflush(stdin);
			printf("Enter password:\n");
			gets(c.password);
			fwrite(&c,sizeof(c),1,studentinfo);
			fclose(studentinfo);
			printf("Sign up successful\n");
			printf("Enter any key to continue...\n");
			getch();
			system("cls");
		}
		else if (choice3==0)
		{
			exit(0);
		}
		}	
	 }
	 else{
		printf("Invalid choice\n");
		printf("Enter any key to exit...");
		getch();
		exit(0);
	 }
	return 0;
}
