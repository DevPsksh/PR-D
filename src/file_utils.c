//
// Created by Ayoub IDEL  on 25/02/2019.
//

#include "file_utils.h"

//TODO : BUG TIME (Synchronisation failed)
//TODO : ADD INTO LOG FILE ERRORS


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

//int main()
//
//{
//
//
//    char* test = loadFileIntoArray("testfile.csv");
//    //printf("text : \n %s \n", test);
//
//    char **rows;
//    int j;
//
//    rows = NULL; //getColumns() requires it to be NULL. (Avoid dangling pointers, leaks e.t.c).
//
//    getColumns( test, "\n", &rows);
//    for ( int i = 0; rows[ i ]; i++) {
//        {
//            printf("Line[ %d ] = %s\n", i, rows[ i ] );
//            char **columnX = NULL;
//            getColumns( rows[ i ], ";", &columnX);
//            for ( j = 0; columnX[ j ]; j++)
//                printf("  Col[ %d ] = %s\n", j, columnX[ j ] );
//            free( columnX );
//        }
//    }
//
//    free( rows );
//    rows = NULL;
//
//    return 0;
//}
