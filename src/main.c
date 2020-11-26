//
// Trace analysis usage: ./Finn_traceanalysis {trace} {timeinterval}
// @param trace : Compressed or not of pcap is fine.
// @param timeinterval :plese assign this to positive interger (exclude 0)
//


#include "libtrace.h"
#include "trace_analysis.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> 


int main(int argc, char *argv[])
{
        
        
        libtrace_t *trace = NULL;
        libtrace_packet_t *packet = NULL;
        Table_Size = 16384; 
        Table_Amount = 10;
        next_report_time = 0;
        strcpy(Ouput_FileName,"/mnt/c/Users/Lab108/Desktop/1120/");


        if (argc < 5) {
                fprintf(stderr, "Usage: %s inputURI\n", argv[0]);
                return 1;
        }

        packet = trace_create_packet();

        if (packet == NULL) {
                perror("Creating libtrace packet");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        trace = trace_create(argv[1]);

        if (trace_is_err(trace)) {
                trace_perror(trace,"Opening trace file");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        if (trace_start(trace) == -1) {
                trace_perror(trace,"Starting trace");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        invalTime = strtoul(argv[3],NULL,10);

        if(invalTime<=0)
        {
                invalTime = 1;
        }

        strcat(Ouput_FileName,argv[2]);
                Deviation = strtoul(argv[4],NULL,10);

        Output_Init();
        import_inverse_cdf_table(Table_Amount);
        import_HeadTail_table();
        import_inverse_cdf_stage_table(Table_Amount);
        while (trace_read_packet(trace,packet)>0) {
                
                per_packet(packet);
                
        }
        //Items_Processing();     
        Close_Output_File();


        if (trace_is_err(trace)) {
                trace_perror(trace,"Reading packets");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        libtrace_cleanup(trace, packet);
        return 0;
}

