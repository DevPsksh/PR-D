#include<stdio.h>
#include <stdlib.h>
#include <mpi.h>

// to compile
// mpicc a.c -o a
// mpirun -np 4 a
/*
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //printf("Hello from processus : %d of %d \n", rank, world_size);


  if(rank == 0) {

  	int to_send = 1;

  	MPI_Ssend(&to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  	MPI_Ssend(&to_send, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
  	MPI_Ssend(&to_send, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
  	MPI_Ssend(&to_send, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  	MPI_Ssend(&to_send, 1, MPI_INT, 5, 0, MPI_COMM_WORLD);

  	int sum = 0;
  	int local[5] = {0, 0, 0, 0, 0};
  	MPI_Recv(&local[1], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&local[2], 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&local[3], 3, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&local[4], 4, MPI_INT, 4, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&local[0], 5, MPI_INT, 5, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


  	for(int i= 0; i<5; i++)
  		sum += local[i];

printf("je suis %d, et [%d, %d, %d, %d, %d] le total recu est = %d\n", rank,local[1], local[2],local[3],local[4],local[0], sum);
  } else {

  	int received =0;

  	MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  	int operation = received * 10 * rank;
  	printf("je suis %d, et j'ai recu %d operation = %d\n", rank, received, operation);

  	MPI_Ssend(&operation, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }


  MPI_Finalize();


  return 0;
}
*/


#include <time.h>

typedef struct {
    int rows;
    int cols;
    int *data;
} MATRIX;


MATRIX *newMatrix(int rows, int cols);
int deleteMatrix(MATRIX *mtx);
MATRIX *copyMatrix(MATRIX *mtx);
int setElement(MATRIX *mtx, int row, int col, int val);
int getElement(MATRIX *mtx, int row, int col, int *val);
int nRows(MATRIX *mtx, int *n);
int nCols(MATRIX *mtx, int *n);
int printMatrix(MATRIX *mtx);
int* getRow(MATRIX *mtx, int num);
void setRow(MATRIX *mtx, int* array, int num);











typedef struct {
    int info;
    int *elements;
    MATRIX *matrix;
} DATA;



typedef struct Node_t {
    DATA data;
    struct Node_t *prev;
} NODE;


/**
 * the HEAD of the Queue, hold the amount of node's that are in the queue
 */
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;


Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);












/**
 * Client Side
 */
typedef struct {
    int total_cost;
    int *elements;
    int *distances;
} DATA_CLIENT;


DATA_CLIENT *getMinimumOfDataClients(DATA_CLIENT **all_data_clients, int num_elements, int SIZE);
void getArrayOfDataClients(MATRIX *all_leaves, MATRIX *mtx_distances, DATA_CLIENT **my_array);
int deleteDataClient(DATA_CLIENT *data_client);

void createDataClientArray(DATA_CLIENT **my_array, int size);
void addDataClient2Array(DATA_CLIENT **my_array, DATA_CLIENT* data_client, int SIZE, int pos);
void printDataClient(DATA_CLIENT* data_client, int size);










char *loadFileIntoArray(char *filename);
int getColumns(const char *const line, const char *const delim, char ***out_storage);
MATRIX* loadFileIntoMatrix(char* filename, int size);

int write2FileMatrix(char const *filename, MATRIX* matrix, char* msg);
int write2FileDataClient(char const *filename, DATA_CLIENT* data_client, int size, char* msg);
int write2FileErrorMessage(char const *filename, char const *msg);
int write2FileInfoMessage(char const *filename, char const *msg);
int write2FileInfoMessageInt(char const *filename, char const *msg, int val);









//ARRAYS
int *copy1DArray(int const *array, int len);
int factorial(int const n);
int **new2DArray(int rows, int columns);
void delete2DArray(int **matrix, int cols);
void show2DArray(int **array, int const rows, int const cols);
int *new1DArray(int size);
void delete1DArray(int *array);
void show1DArray(int *array, int size);
int *swap(int const *array, int size, int pos1, int pos2);
int **generate_next_level(int const *array, int fixed, int SIZE);

//MATRIX
MATRIX *generateNextLevel(int const *array, int fixed, int SIZE);
MATRIX *generateLeaves(int const *array, int SIZE, int fixed);
int* getArrayOfDistances(MATRIX *matrix, int* array);


int getTotalCost(int *a_costs, int size);
int getMinimumCost(int *a_total_costs, int size);
MATRIX* convert2DArrayToMatrix(int **array, int rows, int cols);





#define TRUE 1
#define FALSE 0

/**
 * constructs a queue
 * @param limit
 * @return
 */
Queue *ConstructQueue(int limit) {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }
    if (limit <= 0) {
        limit = 65535;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

/**
 *  destructs a queue
 * @param queue
 */
void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        free(pN);
    }
    free(queue);
}

/**
 * add an element to the queue
 * @param pQueue
 * @param item
 * @return
 */
int Enqueue(Queue *pQueue, NODE *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (item == NULL)) {
        return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }
    /*the queue is empty*/
    item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;

    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;
    return TRUE;
}

/**
 * remove an element from the queue
 * @param pQueue
 * @return
 */
NODE *Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    NODE *item;
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return item;
}

/**
 * verify if the queue is empty
 * @param pQueue
 * @return
 */
int isEmpty(Queue *pQueue) {
    if (pQueue == NULL) {
        return FALSE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>


/**
 * Creates a Matrix with rows Rows & cols Columns initialized
 * with 0
 * @param rows number of rows
 * @param cols number of columns
 * @return pointer to the new MATRIX created or NULL if rows <= 0
 * or cols <= 0
 */
MATRIX *newMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return NULL;

    MATRIX *m = (MATRIX *) malloc(sizeof(MATRIX));

    m->rows = rows;
    m->cols = cols;

    m->data = (int *) malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows * cols; i++)
        m->data[i] = 0;

    return m;
}


/**
 * Frees mtx form the the momery
 * @param mtx
 * @return either -1 if mtx is NULL or 0 if successfully deleted
 */
int deleteMatrix(MATRIX *mtx) {
    if (!mtx)
        return -1;

    assert (mtx->data);
    free(mtx->data);

    free(mtx);

    return 0;
}

#define ELEMENT_AT(mtx, row, col) mtx->data[(col-1) * mtx->rows + (row-1)]


/**
 * Copies MATRIX mtx in another MATRIX cp
 * @param mtx matrix to copy
 * @return either pointer to the copied matrix or NULL if mtx is NULL
 */
MATRIX *copyMatrix(MATRIX *mtx) {
    if (!mtx)
        return NULL;

    MATRIX *cp = newMatrix(mtx->rows, mtx->cols);

    memcpy(cp->data, mtx->data, mtx->rows * mtx->cols * sizeof(int));

    return cp;
}


/**
 * Sets the value at position (row, col) to val
 * @param mtx matrix
 * @param row position of row
 * @param col position of column
 * @param val the new value
 * @return 0 if successfully set, -1 if mtx is NULL, and -2 if row or col
 * are outside of the dimensions of mtx
 */
int setElement(MATRIX *mtx, int row, int col, int val) {
    if (!mtx)
        return -1;

    assert (mtx->data);

    if (row <= 0 || row > mtx->rows || col <= 0 || col > mtx->cols)
        return -2;

    ELEMENT_AT(mtx, row, col) = val;
    return 0;
}


/**
 * Gets an element of the matrix
 * @param mtx the matrix
 * @param row number of row
 * @param col number of column
 * @param val value of the element at (row, col)
 * @return 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx
 */
int getElement(MATRIX *mtx, int row, int col, int *val) {
    if (!mtx || !val)
        return -1;
    assert (mtx->data);

    if (row <= 0 || row > mtx->rows || col <= 0 || col > mtx->cols)
        return -2;

    *val = ELEMENT_AT(mtx, row, col);
    return 0;
}


/**
 * Sets
 * @param mtx
 * @param n
 * @return 0 if successful and -1 if mtx is NULL
 */
int nRows(MATRIX *mtx, int *n) {
    if (!mtx || !n) return -1;
    *n = mtx->rows;
    return 0;
}


/**
 *
 * @param mtx
 * @param n
 * @return 0 if successful and -1 if mtx is NULL
 */
int nCols(MATRIX *mtx, int *n) {
    if (!mtx || !n) return -1;
    *n = mtx->rows;
    return 0;
}


/**
 * Prints the matrix on the screen
 * @param mtx
 * @return 0 if successful
 * and -1 if mtx is NULL
 */
int printMatrix(MATRIX *mtx) {
    if (!mtx)
        return -1;

    int row, col;
    for (row = 1; row <= mtx->rows; row++) {
        for (col = 1; col <= mtx->cols; col++) {
            // Print the floating-point element with
            //  - either a - if negative or a space if positive
            //  - at least 3 spaces before the .
            //  - precision to the hundredths place
            printf("  %d   ", ELEMENT_AT(mtx, row, col));
        }
        // separate rows by newlines
        printf("\n");
    }
    return 0;
}

/**
 *
 * @param mtx
 * @param num
 * @return
 */
int *getRow(MATRIX *mtx, int num) {

    int *array = new1DArray(mtx->cols);

    if (num > mtx->rows || num <= 0) {
        printf("ERROR : impossible to get that row, please verify the number of row\n");//TODO : Log file
        return NULL;
    } else {
        for (int i = 0; i < mtx->cols; ++i) {
            getElement(mtx, num, i+1, &array[i]);
        }
        return array;
    }

}

/**
 *
 * @param mtx
 * @param array
 * @param num
 */
void setRow(MATRIX *mtx, int *array, int num) {
    for (int i = 0; i < mtx->cols; ++i) {
        setElement(mtx, num, i+1, array[i]);
    }
}




/**
 * Copies 1D array into another 1D array
 * @param array the array to copy
 * @param size lenght of the array
 * @return copied array with the same size
 */
int *copy1DArray(int const *array, int size) {
    int *copied = malloc(size * sizeof(int));
    memcpy(copied, array, size * sizeof(int));
    return copied;
}

/**
 * Calculates the factoriel of a value
 * @param n the value
 * @return the factorial of the value or prints an error on the screen
 */
int factorial(int const n) {
    int factorial = 1;
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else
        for (int i = 1; i <= n; ++i)
            factorial *= i;

    return factorial;
}

/**
 * Swap two values of an array
 * @param array the current array
 * @param size lenght of the array
 * @param pos1 the position of the first element
 * @param pos2 the positon of the second element
 * @return the new array with the values in both positions swapped
 */
int *swap(int const *array, int size, int pos1, int pos2) {
    int *copy = copy1DArray(array, size);
    int temp = copy[pos1];
    copy[pos1] = copy[pos2];
    copy[pos2] = temp;
    return copy;
}

/**
 * Creates a 2D array
 * @param rows number of rows
 * @param cols number of columns
 * @return 2D array
 */
int **new2DArray(int rows, int cols) {
    int **array = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < cols; i++) {
        array[i] = (int *) malloc(cols * sizeof(int));
    }

    return array;
}

/**
 * Frees the memory
 * @param matrix
 * @param cols
 */
void delete2DArray(int **matrix, int cols) {
    for (int i = 0; i < cols; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

/**
 * Creates a 1D array
 * @param size
 * @return
 */
int *new1DArray(int size) {
    int *array = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        array[i] = 0;

    return array;
}

/**
 * Frees the memory
 * @param array
 */
void delete1DArray(int *array) {
    free(array);
}

/**
 * Prints 2D array on the screen
 * @param array
 * @param rows
 * @param cols
 */
void show2DArray(int **array, int const rows, int const cols) {
    //printf("ShowMatrix :\n");
    printf("[\n");
    for (int i = 0; i < rows; i++) {
        printf(" [");
        for (int j = 0; j < cols; j++) {
            printf("  %d  ", array[i][j]);
        }
        printf(" ]\n");
    }
    printf("]\n");
}

/**
 * Prints 1D array on the screen
 * @param array
 * @param size
 */
void show1DArray(int *array, int size) {
    printf("[");
    for (int j = 0; j < size; j++) {
        printf("  %d  ", array[j]);
    }
    printf(" ]\n");
}

/**
 * //TODO : this method must be deleted
 * //TODO : NEVER USE THIS
 * @param array
 * @param fixed
 * @param SIZE
 * @return
 */
int **generate_next_level(int const *array, int fixed, int SIZE) {
    int size_level_plus_1 = SIZE - fixed;
    int **result = new2DArray(size_level_plus_1, SIZE);

    //array copied
    int *temp = copy1DArray(array, SIZE);

    for (int i = 0; i < size_level_plus_1; i++) {
        result[i] = swap(temp, SIZE, fixed, fixed + i);
    }
    return result;
}

/**
 * //TODO : this method must be deleted
 * //TODO : NEVER USE THIS
 * @version 1.0
 * @param array
 * @param fixed
 * @return
 */
int **generate_n_level(int const *array, int fixed, int SIZE) {

    int *array_copy = copy1DArray(array, SIZE);
    int leaves_level = factorial(SIZE);
    int **tmp = new2DArray(1, SIZE);

    for (int i = 0; i < SIZE; i++) {
        tmp[0][i] = array[i];
    }
    //show_matrix(tmp, 1, SIZE);

    int **result = new2DArray(leaves_level, SIZE);

    tmp = generate_next_level(array_copy, fixed, SIZE);
    show2DArray(tmp, SIZE, SIZE);
    for (int i = 1; i < SIZE; i++) {
        int **tmp2 = new2DArray(SIZE * (SIZE - i), SIZE);
        printf("i = %d \n", i);
        int count = 0;
        int size_current_level = factorial(SIZE) / factorial(SIZE - i);
        for (int j = 0; j < size_current_level; ++j) {
            //show_matrix(generate_next_level(tmp[j], i), SIZE-i, SIZE);
            for (int k = 0; k < (SIZE - i); ++k) {
                tmp2[count] = generate_next_level(tmp[j], i, SIZE)[k];
                count++;
            }
            printf("tmp2 = %d \n ", j);
            show2DArray(tmp2, count, SIZE);
        }
        printf("tmp  \n ");
        memcpy(tmp, tmp2, sizeof(int) * count * SIZE);
        show2DArray(tmp, count, SIZE);
    }

    return tmp;
}

/**
 * Generates all leaves of a node
 * @version 1.2
 * @param array
 * @param fixed
 * @param SIZE
 * @return
 */
MATRIX *generateNextLevel(int const *array, int fixed, int SIZE) {
    int size_level_plus_1 = SIZE - fixed;
    MATRIX *rslt = newMatrix(size_level_plus_1, SIZE);

    for (int j = 0; j < rslt->rows; ++j) {
        for (int i = 0; i < rslt->cols; ++i) {
            setElement(rslt, j + 1, i + 1, array[i]);
        }
    }

    int tmpp = 0;
    for (int i = 0; i < size_level_plus_1; i++) {
        setElement(rslt, i + 1, fixed + 1, array[fixed + i]);
        setElement(rslt, i + 1, fixed + 1 + i, array[fixed]);
    }

    return rslt;
}



 /**
  * Final version of Generator of leaves
  * @param array
  * @param SIZE
  * @param fixed
  * @return
  */
 MATRIX *generateLeaves(int const *array, int SIZE, int fixed) {


     MATRIX *mtx_tmp = generateNextLevel(array, fixed, SIZE);
     //printf("PrintMatrix\n");
     //printMatrix(mtx_tmp);
     for (int i = 1; i < SIZE-fixed; i++) {
         MATRIX *mtx_tmp2 = newMatrix(factorial(SIZE - fixed) / factorial(SIZE - i - 1 - fixed), SIZE);
         //printf("i = %d \n", i);
         int count = 0;
         int size_current_level = factorial(SIZE - fixed) / factorial(SIZE - i - fixed);
         for (int j = 0; j < size_current_level; ++j) {
             //printf("j = %d \n", j);
             MATRIX *mtx_tmp3 = generateNextLevel(getRow(mtx_tmp, j + 1), i + fixed, SIZE);
             //printf("print tmp3 at j = %d\n", j);
             //printMatrix(mtx_tmp3);
             for (int k = 0; k < (SIZE - i - fixed); ++k) {
                 //printf("k = %d \n", k);
                 setRow(mtx_tmp2, getRow(mtx_tmp3, k + 1), count + 1);
                 count++;
             }
             //printf("tmp2 j = %d , count = %d \n ", j, count);
             //printMatrix(mtx_tmp2);

             deleteMatrix(mtx_tmp3);
         }
         //printf("tmp  i = %d \n ", i);
         mtx_tmp = copyMatrix(mtx_tmp2);
         deleteMatrix(mtx_tmp2);
         //printMatrix(mtx_tmp);
     }
     //printf("---------------------\n");
     //printf("final matrix : fixed = %d rows = %d  cols = %d \n", fixed, mtx_tmp->rows, mtx_tmp->cols);
     //printMatrix(mtx_tmp);
     //printf("----------------------\n");
     return mtx_tmp;
 }

 /**
  * Gives the array of distances of a specific array
  * @param matrix
  * @param array
  * @return
  */
int *getArrayOfDistances(MATRIX *matrix, int *array) {

    //TODO : Verify the size

    int size_array = matrix->cols;
    int *result = new1DArray(size_array);

    int value = 0;

    for (int i = 0; i < size_array - 1; ++i) {
        getElement(matrix, array[i], array[i + 1], &value);
        result[i] = value;
        //printf("result[%d] = %d\n", i, result[i]);
    }

    return result;
}

/**
 * Calculate the total cost of an array
 * @param a_costs array of costs
 * @return total value
 */
int getTotalCost(int *a_costs, int size) {
    if (a_costs == NULL)
        return 0;

    int total = 0;

    for (int i = 0; i < size; i++) {
        total += a_costs[i];
    }
    return total;
}

/**
 * Find the minimum value of an array
 * @param a_total_costs array of total costs
 * @return minimum cost
 */
int getMinimumCost(int *a_total_costs, int size) {
    if (a_total_costs == NULL)
        return 0;

    int minimum = a_total_costs[0];

    for (int i = 1; i < size; i++) {
        if (minimum > a_total_costs[i]) {
            minimum = a_total_costs[i];
        }
    }
    return minimum;
}

/**
 *
 * @param array
 * @param rows
 * @param cols
 * @return
 */
MATRIX *convert2DArrayToMatrix(int **array, int rows, int cols) {

    MATRIX *matrix = newMatrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            setElement(matrix, i + 1, j + 1, array[i][j]);
        }
    }

    return matrix;
}



/**
 * Reads line from a specific file
 * @param file the path to the file
 * @return
 *
 * //TODO : ADD ERROR MESSAGE TO THE LOG FILE
 */
const char *readLine(FILE *file) {

    if (file == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
        if (count == maximumLineLength) {
            maximumLineLength += 128;
            lineBuffer = realloc(lineBuffer, maximumLineLength);
            if (lineBuffer == NULL) {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        }
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';
    char line[count + 1];
    strncpy(line, lineBuffer, (count + 1));
    free(lineBuffer);
    const char *constLine = line;

    return constLine;
}


/**
 * Gets the elements of a specific line
 * For more that 100 columns or lines (when delimiter = \n),
 * minor modifications are needed
 *
 * @param line
 * @param delim
 * @param out_storage
 * @return
 */
int getColumns(const char *const line, const char *const delim, char ***out_storage) {
    const char *start_ptr, *end_ptr, *iter;
    char **out;
    int i;
    int tokens_found = 1, delim_size, line_size;
    int start_idx[100], end_idx[100];

    if ( *out_storage != NULL )                 return -4;
    if ( !line || !delim )                      return -1;
    if ( (delim_size = strlen( delim )) == 0 )  return -2;

    start_ptr = line;
    while ( ( end_ptr = strstr( start_ptr, delim ) ) ) {

        start_idx[ tokens_found -1 ] = start_ptr - line;
        end_idx[ tokens_found - 1 ] = end_ptr - line;
        tokens_found++;
        start_ptr = end_ptr + delim_size;
    }

    for ( iter = start_ptr; (*iter!='\0') ; iter++ );

    start_idx[ tokens_found -1 ] = start_ptr - line;
    end_idx[ tokens_found -1 ] = iter - line;

    line_size = iter - line;

    int size_ptr_region = (1 + tokens_found)*sizeof( char* );
    out = (char**) malloc( size_ptr_region + ( line_size + 1 ) + 5 );
    *out_storage = out;

    for ( i = 0; i < tokens_found; i++ )
        out[ i ] = (char*) out + size_ptr_region + start_idx[ i ];

    out[ tokens_found ] = (char*) NULL;
    char *str_region = (char*) out + size_ptr_region;
    memcpy( str_region, line, line_size );

    for( i = 0; i < tokens_found; i++) str_region[ end_idx[ i ] ] = '\0';


    return tokens_found;
}


/**
 * Puts the whole test file into a char array
 * @param filename
 * @return
 */
char *loadFileIntoArray(char *filename) {

    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( filename , "rb" );
    if( !fp ) perror(filename),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    // allocate memory for entire content
    buffer = calloc( 1, lSize+1 );
    if( !buffer )
        fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    // copy the file into the buffer
    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);

    return buffer;
}


/**
 * Puts the csv file's data into a matrix
 * @param filename
 * @param size
 * @return
 */
MATRIX* loadFileIntoMatrix(char* filename, int size) {
    char* test = loadFileIntoArray(filename);
    char **rows;
    MATRIX* matrix = newMatrix(size, size);
    rows = NULL;
    getColumns(test, "\n", &rows);
    for ( int i = 0; rows[ i ]; i++) {
        //printf("Line[ %d ] = %s\n", i, rows[ i ] );
        char **columnX = NULL;
        getColumns(rows[i], ";", &columnX);
        for ( int j = 0; columnX[ j ]; j++) {
            //printf("  Col[ %d ] = %s\n", j, columnX[ j ] );
            setElement(matrix,i+1, j+1, atoi(columnX[j]));
        }

        free( columnX );
    }
    free( rows );
    rows = NULL;

    return matrix;
}

/**
 *
 * @param filename
 * @param matrix
 * @param msg
 * @return
 */
int write2FileMatrix(char const *filename, MATRIX* matrix, char* msg) {

    FILE *file = fopen(filename, "a+");
    if(file == NULL)
        return -1;

    //Add Time
    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);


    int val = 0;
    fprintf(file, "[%s][INFO] : %s\n", buff, msg);
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            getElement(matrix, i+1, j+1, &val);
            fprintf(file, " %d  ", val);
        }
        fprintf(file, "\n");
    }

    //fprintf(file, "\n");
    fclose(file);
    return 0;
}

/**
 *
 * @param filename
 * @param data_client
 * @param size
 * @param msg
 * @return
 */
int write2FileDataClient(char const *filename, DATA_CLIENT* data_client, int size, char* msg) {

    FILE *file = fopen(filename, "a+");
    if(file == NULL)
        return -1;

    //Add Time
    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(file, "[%s][INFO] : %s\n", buff, msg);
    //print array of elements
    fprintf(file, "Elements : [");
    for (int i = 0; i < size; ++i) {
        fprintf(file, " %d ", data_client->elements[i]);
    }
    fprintf(file, "]\n");
    //print array of distances
    fprintf(file, "Distances : [");
    for (int i = 0; i < size-1; ++i) {
        fprintf(file, " %d ", data_client->distances[i]);
    }
    fprintf(file, "]\n");
    // print total cost
    fprintf(file, "Total cost : %d \n", data_client->total_cost);

    //fprintf(file, "\n");
    fclose(file);

    return 0;
}

/**
 *
 * @param filename
 * @param msg
 * @return
 */
int write2FileErrorMessage(char const *filename, char const *msg) {

    FILE *file = fopen(filename, "a+");
    if(file == NULL)
        return -1;

    //Add Time
    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(file, "[%s][ERROR] : %s\n", buff, msg);

    //fprintf(file, "\n");
    fclose(file);
    return 0;
}

/**
 *
 * @param filename
 * @param msg
 * @return
 */
int write2FileInfoMessage(char const *filename, char const *msg) {

    FILE *file = fopen(filename, "a+");
    if(file == NULL)
        return -1;

    //Add Time
    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(file, "[%s][INFO] : %s\n", buff, msg);
    //fprintf(file, "\n");

    fclose(file);
    return 0;
}

int write2FileInfoMessageInt(char const *filename, char const *msg, int val) {

    FILE *file = fopen(filename, "a+");
    if(file == NULL)
        return -1;

    //Add Time
    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(file, "[%s][INFO] : %s %d\n", buff, msg, val);
    //fprintf(file, "\n");

    fclose(file);
    return 0;
}



/**
 * Puts in my_array the array of all DATA_CLIENTs with specific
 * elements, distances and total cost
 * @param all_leaves
 * @param mtx_distances
 * @param my_array
 */
void getArrayOfDataClients(MATRIX *all_leaves, MATRIX *mtx_distances, DATA_CLIENT **my_array) {

    *my_array = malloc(all_leaves->rows * sizeof(**my_array));

    for (int i = 0; i < all_leaves->rows; i++) {
        (*my_array)[i].elements = copy1DArray(getRow(all_leaves, i + 1), all_leaves->cols);
        (*my_array)[i].distances = copy1DArray(getArrayOfDistances(mtx_distances, (*my_array)[i].elements),
                                               all_leaves->cols - 1);
        (*my_array)[i].total_cost = getTotalCost((*my_array)[i].distances, all_leaves->cols - 1);

    }
}

/**
 * Gives the minimum of DATA_CLIENT in a DATA_CLIENTS array (lowest cost)
 * @param all_data_clients
 * @param num_elements
 * @return
 */
DATA_CLIENT *getMinimumOfDataClients(DATA_CLIENT **all_data_clients, int num_elements, int SIZE) {

    DATA_CLIENT *result = malloc(sizeof(DATA_CLIENT));

    result->total_cost = (*all_data_clients)[0].total_cost;
    result->elements = copy1DArray((*all_data_clients)[0].elements, SIZE);
    result->distances = copy1DArray((*all_data_clients)[0].distances, SIZE - 1);

    for (int i = 1; i < num_elements; i++) {

        if ((*all_data_clients)[i].total_cost < result->total_cost) {
            result->total_cost = (*all_data_clients)[i].total_cost;
            result->elements = copy1DArray((*all_data_clients)[i].elements, SIZE);
            result->distances = copy1DArray((*all_data_clients)[i].distances, SIZE - 1);
        }

    }

    return result;
}

/**
 * Deletes DATA_CLIENT
 * @param data_client
 * @return
 */
int deleteDataClient(DATA_CLIENT *data_client) {
    if (!data_client)
        return -1;

    assert (data_client->distances);
    free(data_client->distances);

    assert (data_client->elements);
    free(data_client->elements);

    free(data_client);

    return 0;
}

/**
 *
 * @param my_array
 * @param size
 */
void createDataClientArray(DATA_CLIENT **my_array, int size) {

    *my_array = malloc(size * sizeof(**my_array));

}

/**
 *
 * @param my_array
 * @param data_client
 * @param SIZE
 * @param pos
 */
void addDataClient2Array(DATA_CLIENT **my_array, DATA_CLIENT* data_client,int SIZE, int pos) {

    (*my_array)[pos].elements = copy1DArray(data_client->elements, SIZE);
    (*my_array)[pos].distances = copy1DArray(data_client->distances, SIZE);
    (*my_array)[pos].total_cost = data_client->total_cost;


}

void printDataClient(DATA_CLIENT* data_client, int size) {
    printf("DATA_CLIENT cost = %d\n", data_client->total_cost);
    printf("Elements : ");
    show1DArray(data_client->elements, size);
    printf("Distances : ");
    show1DArray(data_client->distances, size-1);
}



























#define SIZE 4
#define CLIENTS 4 //world = 5

////////////////////////////////////////////////////////////////
/////////// New structures to SEND & RECIEVE data //////////////
////////////////////////////////////////////////////////////////

typedef struct {
    int rows;
    int cols;
    int data[SIZE*SIZE];
} MATRIX_ALTERED;

typedef struct {
    int info;
    int elements[SIZE];
} DATA_ALTERED;

typedef struct {
	int elements[SIZE];
	int distances[SIZE-1];
	int total_cost;
} DATA_CLIENT_ALTERED;


/*
MATRIX* newMatrixFromMatrixAltered(MATRIX_ALTERED mtx_altered) {

    MATRIX* mtx = newMatrix(mtx_altered.rows, mtx_altered.cols);
    if(mtx == NULL)
        return NULL;

    for(int i=0 ; i<mtx_altered.rows ; i++) {
        for(int j=0 ; j<mtx_altered.cols ; j++) {
    		setElement(mtx, i+1, j+1, mtx_altered.elements[i+j+1]);
    	}
    }

    return mtx;
}*/

DATA* newData(DATA_ALTERED data_altered) {

    DATA* data = (DATA*) malloc(sizeof(DATA));
    if(data == NULL)
        return NULL;

    data->elements = (int *) malloc(SIZE * sizeof(int));

    for(int i=0 ; i<SIZE ; i++) {
        data->elements[i] = data_altered.elements[i];
    }

    data->info = data_altered.info;

    return data;
}

int deleteData(DATA* data) {
    if (!data)
        return -1;

    assert (data->elements);
    free(data->elements);

    // free data itself
    free(data);

    return 0;
}

int printData(DATA *data) {
    if (!data)
        return -1;

    printf("\nfixed = %d\nelements : [", data->info);  
    for (int i = 0; i < SIZE; i++) {      
            printf("  %d  ", data->elements[i]);      
    }
	printf("]\n");
    return 0;
}








int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);


	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);


	////////////////////////////////////////////////////////////////
	///////////////// Create our own MPI_DATA_TYPES ////////////////
	////////////////////////////////////////////////////////////////

	/**MATRIX_ALTERED**/
	/*-------------------------------------------------------------------------------*/

	int blocklengths_matrix[3] = {1, 1, SIZE*SIZE};

	MPI_Aint displacements_matrix[3];
	displacements_matrix[0] = offsetof(MATRIX_ALTERED, rows);
	displacements_matrix[1] = offsetof(MATRIX_ALTERED, cols);
	displacements_matrix[2] = offsetof(MATRIX_ALTERED, data);

	MPI_Datatype types_matrix[3] = {MPI_INT, MPI_INT, MPI_INT};
	MPI_Datatype MPI_MATRIX_ALTERED;

	MPI_Type_create_struct(3, blocklengths_matrix, displacements_matrix, types_matrix, &MPI_MATRIX_ALTERED);
	MPI_Type_commit(&MPI_MATRIX_ALTERED);

	/**DATA_ALTERED**/
	/*-------------------------------------------------------------------------------*/

	int blocklengths_data[2] = {1, SIZE};

	MPI_Aint displacements_data[2];
	displacements_data[0] = offsetof(DATA_ALTERED, info);
	displacements_data[1] = offsetof(DATA_ALTERED, elements);

	MPI_Datatype types_data[2] = {MPI_INT, MPI_INT};
	MPI_Datatype MPI_DATA_ALTERED;

	MPI_Type_create_struct(2, blocklengths_data, displacements_data, types_data, &MPI_DATA_ALTERED);
	MPI_Type_commit(&MPI_DATA_ALTERED);
	

	/**DATA_CLIENT_ALTERED**/
	/*-------------------------------------------------------------------------------*/
	int blocklengths_data_client[3] = {SIZE, SIZE-1, 1};

	MPI_Aint displacements_data_client[3];
	displacements_data_client[0] = offsetof(DATA_CLIENT_ALTERED, elements);
	displacements_data_client[1] = offsetof(DATA_CLIENT_ALTERED, distances);
	displacements_data_client[2] = offsetof(DATA_CLIENT_ALTERED, total_cost);

	MPI_Datatype types_data_client[3] = {MPI_INT, MPI_INT, MPI_INT};
	MPI_Datatype MPI_DATA_CLIENT_ALTERED;

	MPI_Type_create_struct(3, blocklengths_data_client, displacements_data_client, types_data_client, &MPI_DATA_CLIENT_ALTERED);
	MPI_Type_commit(&MPI_DATA_CLIENT_ALTERED);
	

	////////////////////////////////////////////////////////////////
	/////////////////        Things to send         ////////////////
	////////////////////////////////////////////////////////////////
	MATRIX_ALTERED mtx_distances_altered;
	DATA_ALTERED data_altered;
	//DATA_CLIENT_ALTERED data_client_altered;




	////////////////////////////////////////////////////////////////
	///////////////// Things to store after sending ////////////////
	////////////////////////////////////////////////////////////////
	MATRIX* mtx_distances = newMatrix(SIZE, SIZE);
	DATA_CLIENT* data_client;







	//////////////////////SERVER///////////////////////////
	if(rank == 0) {

		for(int i=0 ; i<SIZE ; i++) {
			for(int j=0 ; j<SIZE ; j++) {
				setElement(mtx_distances, i+1, j+1, i+j);
			}
		}		
		mtx_distances_altered.rows = SIZE;
		mtx_distances_altered.cols = SIZE;

		printf("MATRIX DES DISTANCES A ENVOYER : cols = %d, rows = %d\n", mtx_distances_altered.rows, mtx_distances_altered.cols);
		for(int i=0 ; i<SIZE ; i++) {
			for(int j=0 ; j<SIZE ; j++) {
				mtx_distances_altered.data[i+j+1] = ELEMENT_AT(mtx_distances, i+1, j+1);
				printf("  %d  ", mtx_distances_altered.data[i+j+1]);
			}
			printf("\n");
		}

		for(int i=1 ; i<world_size ; i++) {
			MPI_Ssend(&mtx_distances_altered, 1, MPI_MATRIX_ALTERED, i, 0, MPI_COMM_WORLD);
		}


		int fixed = 0;
    	int array[] = {1, 2, 3, 4};

		//Generate next level
	    MATRIX *matrix_next_level = generateNextLevel(array, fixed, SIZE);
	    //printf("matrice next level : \n");
	    //printMatrix(matrix_next_level);

	    //Create a queue
   		 Queue *queue = ConstructQueue(SIZE);

	    //Add each node of the first next level to the queue
	    NODE *node;
	    for (int i = 0; i < matrix_next_level->rows; ++i) {
	        node = (NODE *) malloc(sizeof(NODE));
	        node->data.info = fixed;
	        node->data.elements = getRow(matrix_next_level, i + 1);
	        node->data.matrix = copyMatrix(mtx_distances);
	        Enqueue(queue, node);
	    }

	    deleteMatrix(matrix_next_level);

	    printf("--------- \n");
	    printf("Queues : \n");
	    printf("--------- \n");



	    //Define DATA_CLIENT of mins Array
	    //DATA_CLIENT* mins = NULL;
	    //createDataClientArray(&mins, SIZE);



	    //Send nodes to clients
	    for(int i = 1 ; i<world_size ; i++) {

	        node = Dequeue(queue);
/*
	        printf("===================\n");
	        printf("\nDequeued: %d\n", node->data.info);
	        printMatrix(node->data.matrix);
	        show1DArray(node->data.elements, SIZE);
*/
	        

	        for(int j=0 ; j<SIZE;j++) {
	        	data_altered.elements[j] = node->data.elements[j];
	        }
	        data_altered.info = node->data.info;
/*
	        printf("data_altered.elements\n");
	        for(int j=0 ; j<SIZE;j++) {
	        	printf(" %d ", data_altered.elements[j]);
	        }
	         printf("\ndata_altered.info = %d\n", data_altered.info);

*/

	        //we send node to Client i
			MPI_Ssend(&data_altered, 1, MPI_DATA_ALTERED, i, 0, MPI_COMM_WORLD);

			
		

	        free(node);
	    }







	} 








	////////////////////////CLIENTS/////////////////////////////
	else {
		// receive the matrix of distances
		MPI_Recv(&mtx_distances_altered, 1, MPI_MATRIX_ALTERED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//printf("je suis %d MATRIX DES DISTANCES Recue : cols = %d, rows = %d\n", rank, mtx_distances_altered.rows, mtx_distances_altered.cols);


		// store matrix of distances in MATRIX pointer
		for(int i=0 ; i<SIZE ; i++) {
			for(int j=0 ; j<SIZE ; j++) {
				setElement(mtx_distances, i+1, j+1, mtx_distances_altered.data[i+j+1]);
			}
		}	
		//printMatrix(mtx_distances);	


		//Receive specific node
		MPI_Recv(&data_altered, 1, MPI_DATA_ALTERED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		DATA * data = newData(data_altered);
		//printData(data);


		MATRIX* mtx_leaves_actual_node = generateLeaves(data->elements, SIZE, data->info+1);//info = fixed

		//to store all data_clients
		DATA_CLIENT* test = NULL;
        getArrayOfDataClients(mtx_leaves_actual_node, mtx_distances, &test);

        /*		
		for (int k = 0; k < mtx_leaves_actual_node->rows; ++k) {
            printf("struct %d  ->  cost = %d\n", k, test[k].total_cost);
            show1DArray(test[k].elements, SIZE);
            show1DArray(test[k].distances, SIZE-1);
        }
*/
        //printf("===========Print Min DATA_CLIENT===============\n");
        DATA_CLIENT* min = getMinimumOfDataClients(&test, mtx_leaves_actual_node->rows, SIZE);
        //printDataClient(min, SIZE);
		
		
        
		




	}








	MPI_Type_free(&MPI_MATRIX_ALTERED);
	MPI_Type_free(&MPI_DATA_ALTERED);
	MPI_Type_free(&MPI_DATA_CLIENT_ALTERED);




	MPI_Finalize();

	return 0;
}





