#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define stnu(x) x-'0'
//���� 
typedef struct node{	
		char str;
		node*next;
	}node;
//���� 
typedef struct {
    int length;			//����Ϊ��������Ϊ�� 
    int width;
    int **matrix;
} Matrix;
typedef struct{
	int size;
	int* arr;
}Arr;

// Ϊ��������ڴ� 
int **allocateMatrix(int length, int width) {
    int **matrix = (int **)malloc(length * sizeof(int *));
    for (int i = 0; i < length; i++) {
        matrix[i] = (int *)malloc(width * sizeof(int));
    }
    return matrix;
}

//������Ԫ�س�ʼ��ΪĳһԪ�� 
void initalizeMatrix(int a,Matrix* mat){
	for (int i=0;i<mat->length;i++){
		for(int j=0;j<mat->width;j++){
			mat->matrix[i][j]=a;
		}
	}
}

//����һ������ 
Matrix* genmat(int length,int width){ 
	Matrix* mat=(Matrix*)malloc(sizeof(Matrix));
	mat->length=length;
	mat->width=width;
	mat->matrix=allocateMatrix(length,width);
	initalizeMatrix(0,mat);
	return mat;
}

//��ӡ���� 
void printm(Matrix* mat){
	for (int i=0;i<mat->length;i++){
		for(int j=0;j<mat->width;j++){
			printf("%d ",mat->matrix[i][j]);
		}
		printf("\n");
	}
}

//�С��� 
int rmc(Matrix*A,int a,Matrix*B,int b){
	int sum=0;
	for (int i=0;i<A->width;i++){
		 sum+=A->matrix[a][i]*B->matrix[i][b];
	}
	return sum;
}

//����˷� 
Matrix* matmul(Matrix*A,Matrix*B){
	if(A->length!=B->width){
		printf("����ά�Ȳ�ƥ��"); 
		 return NULL;
	}
	Matrix *C=genmat(A->length,B->width);
	for (int i=0;i<C->length;i++){
		for(int j=0;j<C->width;j++){
			C->matrix[i][j]=rmc(A,i,B,j);
		}
	}
	return C;	
}
//k*matrix
Matrix* kmatmul(int k,Matrix*A){
	Matrix*C=genmat(A->length,A->width);
	for (int i=0;i<C->length;i++){
		for(int j=0;j<C->width;j++){
			C->matrix[i][j]=k*A->matrix[i][j];
		}
	}
	return C;
}

//������ɾ��� 
Matrix* randm(int length,int width ){
	srand(time(NULL));
	Matrix*C=genmat(length,width);
	for (int i=0;i<C->length;i++){
		for(int j=0;j<C->width;j++){
			C->matrix[i][j]=rand();
		}
	}
	return C;
}

//ָ����Χ���ɾ��� 
Matrix* randi(int rows, int cols, int a, int b) {
    int i, j;
    srand(time(0)); 


   Matrix*C=genmat(rows,cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
           C->matrix[i][j] = a + rand() % (b - a + 1);
        }
    }
	return C;
}

//��ӡ���� 
void printl(node*list){
	node*ptr=list->next ;
	while(ptr!=NULL){
		printf("%c",ptr->str);
		ptr=ptr->next;
	}
} 

//���������� 
int lenlist(node*list){
	node*ptr=list->next;
	int cnt=1;
	while(ptr->next!=NULL){
		cnt++;
		ptr=ptr->next;
	}
	return cnt;
}
//�ͷ������ڴ� 
void FreeList(node* head) {
    node* current = head;
    node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
//�ͷž����ڴ�
void Freemat(Matrix*mat){
	for(int j=0;j<mat->length;j++){
                free(mat->matrix[j]);
            }
            free(mat->matrix);
            free(mat);
} 
//���ƾ��� 
Matrix* awritem(Matrix*mat,int** num){
	for(int i=0;i<mat->length;i++){
		for(int j=0;j<mat->width;j++){
			mat->matrix[i][j]=num[i][j];
		}
	}
	return mat;
}

//������Ƭ 
Matrix* matsli(Matrix*ori,Arr*a,Arr*b) {
	int length=a->size;
	int width=b->size;
	Matrix*mat=genmat(length,width);
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			mat->matrix[i][j]=ori->matrix[a->arr[i]][b->arr[j]];
		}
	}
	return mat;
}

//����0��1��2������������ 
Arr*randa(int length){
	Arr*a=(Arr*)malloc(sizeof(Arr));
	a->size=length;
	a->arr=(int*)malloc(sizeof(int)*a->size);
	for(int i=0;i<length;i++){
		a->arr[i]=i;
	}
	return a; 
}

//������� 
Matrix*scanm(){
	node *list=(node*)malloc(sizeof(node));
	list->next=NULL;
	node *last=(node*)malloc(sizeof(node));
	last->next=NULL;
	char c;
	int sta=0;//ָʾ�Ƿ��˳� 
	int sem=0;
	do{
		c=getchar();
		if(c==';'){
			sem++;
		}
		node*Node=(node*)malloc(sizeof(node));
		if(sta==0){		//��������洢���� 
			list->next=Node;
		}
		Node->str=c;
		last->next= Node;
		last=last->next;
		last->next=NULL;
		sta=1;
	}
	while(c!=']');
	node *ptr=list->next; 
	//printl(list);//test
	// 
	sta=0;
	int cnt=0,i=0,j=0,width=0,length=0;//sta1ָʾ�Ƿ�Ӧ���˳�ѭ�� 
	Matrix* num=genmat(sem+1,lenlist(ptr)/(sem+1));//����һ���㹻�������洢���� 
	do{
        if (ptr->str<='9'&&ptr->str>='0' ) {//��¼���� 
            cnt=cnt*10+stnu(ptr->str);
            ptr=ptr->next;
           
        }
        else if(ptr->str== ',' || ptr->str == ' '){//�������źͿո���Ϊһ�������Ѿ��������룬д�����飬����������� 
        	num->matrix[i][j]=cnt;
        	j++;
        	cnt=0;
        	ptr=ptr->next;	
		}
		 else if(ptr->str == '\n'){
		 ptr=ptr->next;
		 } 
		else if(ptr->str==';'){//�����ֺŻ��� 
			num->matrix[i][j]=cnt;
			width=j+1;
			length=i+1;
        	j=0;
        	i++;
        	cnt=0;
        	ptr=ptr->next;
		}
		else if(ptr->str=='['){
			ptr=ptr->next;
		}
		else if(ptr->str==']'){
			sta=1;
			num->matrix[i][j]=cnt;	
			width=j+1;
			length=i+1;
			}
		
		else{
			printf("��Ѿ�ģ���ɶ�أ�"); }	
    }while ( sta!=1) ;
   // printm(num);
    Arr*a=randa(length);
    Arr*b=randa(width);
	Matrix* mat=matsli(num,a,b);
	free(num); 
	free(a);
	free(b);
	return mat;
}
//��������ʽ 
Matrix* submat(int a,int b,Matrix* mat){
	Matrix*sub=genmat(mat->length-1,mat->width-1);
	for(int i=0,k=0;i<mat->length-1;i++,k++){
			if(k==a-1){
				k++;
			}
		for(int j=0,l=0;j<mat->width-1;j++,l++){
			 if(l==b-1){
				l++;
			}
			sub->matrix	[i][j]=mat->matrix[k][l] ;
		}
	}

	if((a+b)%2!=0){
		sub=kmatmul(-1,sub);
		}
	printm(sub);
		return sub;	
	}
	
//��������ʽ 
int det(Matrix*mat,int ans){
	if(mat->length>2){
        for(int i=0;i<mat->width;i++){
            Matrix* sub = submat(1,i+1,mat);
            ans += mat->matrix[0][i] * det(sub,ans);
            Freemat(sub);
        }
    }
	if(mat->length==2){
		return mat->matrix[0][0] * mat->matrix[1][1] - mat->matrix[0][1]* mat->matrix[1][0];
	}
	else {
		return ans;
	}
	
}  


int main(){
	Matrix* A=scanm();
	printm(A);
	printf("%d",det(A,0));
	return 0;
} 

