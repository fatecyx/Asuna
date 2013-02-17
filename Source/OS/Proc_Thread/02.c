diff --git a/Thread_Sync.cpp b/Thread_Sync.bak
index ec51a80..964747e 100644
--- a/Thread_Sync.cpp
+++ b/Thread_Sync.bak
@@ -57,7 +57,7 @@ int main()
     union semun arg;
     //声明共享主存
     int *array;
-    int *sum;
+    int *sum_odd, *sum_even;
     int *set;
     int *get;
     int arraysize;
@@ -65,10 +65,12 @@ int main()
     //映射共享主存。该主存区可以被进程共享。
     arraysize = sizeof(int) * MAXSEM;
     array = (int *)mmap(NULL, arraysize,  PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
-    sum  = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
+    sum_odd  = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
+    sum_even  = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
     get   = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
     set   = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
-    *sum = 0;
+    *sum_odd = 0;
+    *sum_even = 0;
     *get = 0;
     *set = 0;
 
@@ -128,11 +130,14 @@ int main()
                 semop(mutxid, &P, 1);
                 if(*get == 100)
                     break;
-                *sum += array[(*get)%MAXSEM];
-                printf("The ComsumerA Get Number %d\n", array[(*get)%MAXSEM] );
-                (*get)++;
-                if( *get ==100)
-                    printf("The sum is %d \n ", *sum);
+                if (*get % 2)
+                {
+                    *sum_odd += array[(*get)%MAXSEM];
+                    printf("The ComsumerA Get Number %d\n", array[(*get)%MAXSEM] );
+                    (*get)++;
+                    if( *get ==100)
+                        printf("The sum is %d \n ", *sum_odd);
+                }
                 semop(mutxid , &V , 1);
                 semop(emptyid , &V ,1 );
                 sleep(1);
@@ -151,11 +156,14 @@ int main()
                     semop(mutxid , &P , 1);
                     if(*get == 100)
                         break;
-                    *sum += array[(*get)%MAXSEM];
-                    printf("The ComsumerB Get Number %d\n", array[(*get)%MAXSEM] );
-                    (*get)++;
-                    if( *get ==100)
-                        printf("The sum is %d \n ", *sum);
+                    if (*get % 2 == 0)
+                    {
+                        *sum_even += array[(*get)%MAXSEM];
+                        printf("The ComsumerB Get Number %d\n", array[(*get)%MAXSEM] );
+                        (*get)++;
+                        if( *get ==100)
+                            printf("The sum is %d \n ", *sum_even);
+                    }
                     semop(mutxid , &V , 1);
                     semop(emptyid , &V ,1 );
                     sleep(1);
