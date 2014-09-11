void FileMan(INTEGER oper, INTEGER filenum, INTEGER datatype, INTEGER length,
             INTEGER offset, INTEGER offtype, void* data, INTEGER PNum)
/****************************************************************
 *                                                              *
 *FileMan(oper,filenum,datatype,length,offset,offtype,data,PNum)*
 *                                                              *
 *  FileMan manages Q-Chem data file manipulation.              *
 *                                                              *
 *  Input:                                                      *
 *    oper     - Type of file operation to be performed         *
 *      FM_OPEN_R    - Open for read                            *
 *      FM_OPEN_W    - Open for write                           *
 *      FM_OPEN_RW   - Open for read/write                      *
 *      FM_READ      - Read (Redundantly in parallel)           *
 *      FM_PREAD     - Read (Independently in parallel)         *
 *      FM_WRITE     - Write (Redundantly in parallel)          *
 *      FM_PWRITE    - Write (Independently in parallel)        *
 *      FM_CLOSE     - Close                                    *
 *      FM_REMOVE    - Remove                                   *
 *    filenum  - File number to be used                         *
 *    datatype - Type of data in r/w operation                  *
 *      FM_BYTE      - Bytes                                    *
 *      FM_DP        - Double precision                         *
 *      FM_INT       - Integer                                  *
 *      FM_LGCL      - QChem LOGICAL                            *
 *    length   - Number of items in r/w operation               *
 *    offset   - Offset to be applied to file before r/w        *
 *               operation, in number of datatype items         *
 *    offtype  - Point from which offset is applied             *
 *      FM_BEG       - Beginning of file                        *
 *      FM_CUR       - Current file position (will not work for *
 *                     cases where PNum>1, i.e., calls from     *
 *                     LongFileMan)                              *
 *    PNum     - Partition number for long files                *
 *                                                              *
 *  Input/Output:                                               *
 *    data     - Used for memory <-> disk transfers             *
 *                                                              *
 ****************************************************************/


