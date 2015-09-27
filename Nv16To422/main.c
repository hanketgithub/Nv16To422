//
//  main.c
//  Nv16To422
//
//  Created by Hank Lee on 9/30/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Nv16To422.h"

int main(int argc, const char * argv[]) {
    int fd_in;
    int fd_out;
    
    uint8_t *y;
    uint8_t *u_et_v;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    
    uint8_t *frame;
    uint8_t *u_dst;
    uint8_t *v_dst;
    
    char *cp;
    char output_file_name[256];

    
    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }
    
    
    rd_sz   = 0;
    width   = 0;
    height  = 0;
    wxh     = 0;
    frame   = NULL;
    u_dst   = NULL;
    v_dst   = NULL;
    cp      = NULL;
    memset(output_file_name, 0, sizeof(output_file_name));
    
    // get input file name from comand line
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // specify output file name
    cp = strchr(argv[1], '.');
    strncpy(output_file_name, argv[1], cp - argv[1]);
    strcat(output_file_name, "_422");
    strcat(output_file_name, cp);
    
    fd_out  = open(output_file_name, O_WRONLY | O_CREAT, S_IRUSR);
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    wxh = width * height;
    
    frame = malloc(wxh * 2);
    u_dst = malloc(wxh / 2);
    v_dst = malloc(wxh / 2);
    
    y = frame;
    u_et_v = y + wxh;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(fd_in, frame, wxh * 2);
        
        if (rd_sz == wxh * 2)
        {
            write(fd_out, y, wxh);
            
            interleave_to_planar
            (
                wxh,
                u_dst,
                v_dst,
                u_et_v
            );
            
            write(fd_out, u_dst, wxh / 2);
            write(fd_out, v_dst, wxh / 2);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    close(fd_in);
    close(fd_out);
    
    printf("Done\n");
    printf("Output file: %s\n", output_file_name);
    
    return 0;
}
