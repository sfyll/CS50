 char ptr[5000];
    int i = 0;
    char filename[15];
    //FILE *img = fopen("img.jpg", "w");
    while(fread(ptr, 1, 512, card) == 512)

 {
        FILE *buffer;
        buffer = malloc(sizeof(char)*5000);
            //check les 4 premier bytes sont des headers de JPEG
            if(ptr[0] == (char)0xff && ptr[1] == (char)0xd8 && ptr[2] == (char)0xff && (ptr[3] & (char)0xf0) == (char)0xe0)
            {
                do
                {
                    i++;
                    fread(ptr, 1, 512, card);
                    fwrite(ptr, 1, 512, buffer);
                }
                while(ptr[0] == (char)0xff && ptr[1] == (char)0xd8 && ptr[2] == (char)0xff && (ptr[3] & (char)0xf0) == (char)0xe0);
                sprintf(filename, "%i.jpg", i++);
                FILE *img = fopen(filename, "w");
                fwrite(ptr, 1, i*512, img);
                fclose(img);
                free(buffer);
                //créer un fichier de type ###.jpg
                //printf("%i\n", i);
            }
            //printf("%hhx-", ptr[0]);
            //printf("%hhx-", ptr[1]);
           // printf("%hhx\n", ptr[2]);
            //printf("Read file %c\n", &ptr[0]);
//            fwrite(ptr, 1, 512, img);
        }
    //printf("Nb lines: %d\n", i);
    fclose(card);
}
