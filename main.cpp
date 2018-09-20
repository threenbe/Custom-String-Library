// StringADT demonstration file main.cpp
#include <stdio.h>
#include <string.h> // declares the built-in C string library functions, like strcat
#include "String.h" // declares our new improved String functions, like utstrcat
#include <stdlib.h> // smh

#define READY_FOR_STAGE_4

void testStage1(void) {
	char p[12];
	const char* q = "Hello World";
	char* s; 
	char* t; 
	unsigned k;
	
	printf("this test should print Hello World three times\n");

	for (k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	s = utstrdup(p);
	printf(s);
	printf("\n");

	q = "you goofed!";
	for (k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	printf(s);
	printf("\n");
	
	t = utstrdup(s);
	utstrfree(s);

	printf(t);	
	printf("\n");
	utstrfree(t);
}	


void testStage2(void) {
	char c_str1[20] = "hello";
	char* ut_str1;
	char* ut_str2;

	printf("Starting stage 2 tests\n");
	strcat(c_str1, " world");
	printf("%s\n", c_str1); // nothing exciting, prints "hello world"

	ut_str1 = utstrdup("hello ");
	ut_str1 = utstrrealloc(ut_str1, 20);
	utstrcat(ut_str1, c_str1);
	printf("%s\n", ut_str1); // slightly more exciting, prints "hello hello world"

	utstrcat(ut_str1, " world");
	printf("%s\n", ut_str1); // exciting, should print "hello hello world wo", 'cause there's not enough room for the second world

	ut_str2 = utstrdup("");
	ut_str2 = utstrrealloc(ut_str2, 11);
	utstrcpy(ut_str2, ut_str1 + 6);
	printf("%s\n", ut_str2); // back to "hello world"

	ut_str2 = utstrrealloc(ut_str2, 23);
	utstrcat(ut_str2, " ");
	utstrcat(ut_str2, ut_str1);
	printf("%s\n", ut_str2); // now should be "hello world hello hello"
 
	utstrfree(ut_str1);
	utstrfree(ut_str2);
}

#define BIG 1000000
void testStage3(void) {
	int k;
	char* ut_str1 = utstrdup("");
	ut_str1 = utstrrealloc(ut_str1, BIG); // big, big string

	printf("attempting stage 3 test. This shouldn't take long...\n");
	printf("(no really, it shouldn't take long, if it does, you fail this test)\n");
	fflush(stdout);

	for (k = 0; k < BIG; k += 1) {
		utstrcat(ut_str1, "*");
	}
	if (ut_str1[BIG-1] != '*') {
		printf("stage3 fails for not copying all the characters\n");
	} else if (strlen(ut_str1) != BIG) {
		printf("Hmmm, stage3 has something wrong\n");
	} else {
		printf("grats, stage 3 passed (unless it took a long time to print this message)\n");
	}
	utstrfree(ut_str1);
}

void testStage5(void){
	printf("starting stage 5, should just print an 11\n");
	uint32_t length;
	char* utstr = utstrdup("Hello World");
	length = utstrlen(utstr);
	printf("%d\n",length);
	utstrfree(utstr);
}

void testStage6(void){
	printf("starting stage 6, should print an 11 and Hello World\n");
	char* utstr = utstrdup("Hello World");//11 chars
	char cstr[20] = ("Goodbye World!");//14 chars
	uint32_t length = utstrlen(utstr);//should be 11
	printf("%d\n",length);//11
	printf("%s\n", utstr);//prints "Hello World"

    printf("Now it should print 11 and Goodbye Wor\n");
	utstrcpy(utstr,cstr);
	length = utstrlen(utstr);
	printf("%d\n",length);//11
	printf("%s\n", utstr);//prints "Goodbye Wor"
    
    printf("Now it should print 13 and Goodbye World\n");
    utstr = utstrrealloc(utstr, 13);
    utstrcpy(utstr,cstr);
    length = utstrlen(utstr);
    printf("%d\n",length);//13
    printf("%s\n",utstr);//"Goodbye World"
    
    printf("Now it should print 14 and Goodbye World! twice\n");
    utstr = utstrrealloc(utstr, 14);
    utstrcpy(utstr,cstr);
    length = utstrlen(utstr);
    printf("%d\n",length);//14
    printf("%s\n",utstr);//"Goodbye World!"

    utstr = utstrrealloc(utstr, 20);
    utstrcpy(utstr,cstr);
    length = utstrlen(utstr);
    printf("%d\n",length);//14
    printf("%s\n",utstr);//"Goodbye World!"

    utstrfree(utstr);
}

void testStage7(void){
    printf("starting stage 7, should print Hitler did nothing wrong.\n");
    char* utstr = utstrdup("Hitler did nothing wrong.");
    printf("%s\n", utstr);
    printf("Now it should print a few words of Mein Kampf.\n");//up to "retur"
    char meinkampf[1000] = ("German-Austria must return to the great German motherland, \nand not because of economic considerations of any sort. No, \nno: even if from the economic point of view this union were \nunimportant, indeed, if it were harmful, it ought nevertheless \nto be brought about.");
    utstrcpy(utstr,meinkampf);
    printf("%s\n", utstr);
    printf("Now it should print the first couple sentences of Mein Kampf.\n");
    utstr = utstrrealloc(utstr, 1000);
    utstrcpy(utstr,meinkampf);
    printf("%s\n", utstr);
    utstrfree(utstr);
}

/*
* utstrdup -> takes a cstring/utstring input and makes a duplicate utstring output 
* utstrlen -> finds length of utstring
* utstrcat -> appends chars from 2nd string onto 1st
* utstrcpy -> copies chars from 2nd string onto 1st
* utstrfree -> frees allocated stuff
* utstrrealloc -> increases utstring capacity to specified value if possible
*/

void testStage8(void){
	printf("Starting stage 8, first a '7' and 'Rangaha' should be printed\n");
	char cstring1[20] = " BukLau";
	char cstring2[50] = "His palms are sweaty, sp-spaghetti";
	char* utstr = utstrdup("Rangaha");
	uint32_t length = utstrlen(utstr);//7
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("Now it should print a '9' and 'Rangaha B'\n");
	utstr = utstrrealloc(utstr,9);
	utstrcat(utstr, cstring1);
	length = utstrlen(utstr);//9
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("Now it should print '14' and 'Rangaha BukLau'\n");
	utstr = utstrrealloc(utstr,16);
	utstrcpy(utstr,"Rangaha");
	utstrcat(utstr,cstring1);
	length = utstrlen(utstr);//14
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("Now it should print '16' and 'His palms are sw'\n");
	utstrcpy(utstr,cstring2);
	length = utstrlen(utstr);//16
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("Finally, this should print '34' and the full cstring2\n");
	utstr = utstrrealloc(utstr,100);
	utstrcpy(utstr,cstring2);
	length = utstrlen(utstr);//34
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("some other sutff idk fam, 41 and cstring2+' BukLau'\n");
	utstrcat(utstr,cstring1);//cstring2 followed by " BukLau"
	length = utstrlen(utstr);//41
	printf("%d\n",length);
	printf("%s\n",utstr);

	printf("last one forreally, prints '2' and 'Yo'\n");
	utstrcpy(utstr,"Yo");
	length = utstrlen(utstr);//2
	printf("%d\n",length);
	printf("%s\n",utstr);

	utstrfree(utstr);
}


#ifdef READY_FOR_STAGE_4
void testStage4(void) {
	//char p[20];
	/*if (! isSaneHeap()) {
		printf("oh goodness! you've corrupted the heap, naughty naughty\n");
		return;
	}
	if (! isEmptyHeap()) {
		printf("Uh Oh! you have a memory leak somewhere, better find it\n");
		return;
	}
	
	 if we reach this point, the heap is OK */
	//printf("woo HOO! the heap is OK, test 4 looks good so far, now we're going to crash...\n");


	/* each of the following lines should crash the program (an assert should fail) 
	 * try each of them in turn to make sure you're catching the obvious mistakes 
	 * just uncomment the line and see what happens (it should crash) 
	 */
	// printf("crashing with utstrlen\n\n\n"); utstrlen("Hello World");	
	// printf("crashing with utstrcpy\n\n\n"); utstrcpy(p, "Hello World");
	// printf("crashing with utstrcat\n\n\n"); utstrcat(p, "Hello World");
	// printf("crashing with utstrfree\n\n\n"); utstrfree((char *)malloc(20));
	// printf("crashing with utstrrealloc\n\n\n"); utstrrealloc((char *)malloc(20), 40);
}
#endif /* READY_FOR_STAGE_4 */

int main(void) {
	testStage1();
	testStage2();
	testStage3(); 
	testStage5();
	testStage6();
	testStage7();
	testStage8();

#ifdef READY_FOR_STAGE_4	
	testStage4();
#endif /* READY_FOR_STAGE_4 */
	return 0;
}