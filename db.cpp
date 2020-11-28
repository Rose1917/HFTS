#include "include/common.h"
int init_db(){
	SAConnection con;
	 try {
        con.Connect(_TSA("129.211.69.209@"), _TSA("root"), _TSA("Hhcl199904020"), SA_MySQL_Client);
        printf("We are connected!\n");

        /*
        The rest of the tutorial goes here!
        */
        
        con.Disconnect();
        printf("We are disconnected!\n");
    }
    catch(SAException &x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
	printf("Preparing to link to the database\n");
	return 0;

}