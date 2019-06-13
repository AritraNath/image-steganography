#include<stdio.h>
#include<string.h>

#define uchar unsigned char 
#define uint unsigned long int 

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))

#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

int i1,i2,i3,i4;
uint parsed_op[100][16],k[64] = {
   0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
   0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
   0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
   0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
   0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
   0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
   0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
   0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
},hash[8] = {
   0x6a09e667,0x367cd507,0x3070dd17,0xf70e5939,0xffc00b31,0x68581511,0x64f98fa7,0xbefa4fa4
};
    
uchar text[256];
void preprocess(uchar text[])
{
    int size,k1,k2,k3,in;
    size=strlen(text);
    
    for(i1=0;i1<=size/64;i1++)
    {
        for(i2=0;i2<16;i2++)
        {
            parsed_op[i1][i2]=0b0;
            for(i3=0;i3<4;i3++)
            {        
                in=i1+i2+i3;
                if (in==size)
                {
					parsed_op[i1][i2] = ((parsed_op[i1][i2]<< 1)|0b1)<<8;
					for(i4=3;i4>i3;i4--)
					{
						parsed_op[i1][i2]=parsed_op[i1][i2]<<8;
						
					}
					break;
					
				}
				parsed_op[i1][i2] = parsed_op[i1][i2]<<8 | text[in];
				
                
            }
        
        }
	}
      
                
    }
    


void main()
{
    uint W[64],a,b,c,d,e,f,g,h,temp1,temp2;
    int i,t,j;
    printf("Enter the text to hashed:");
    gets(text);
    preprocess(text);
    
    for(i=0;i<=i1;i++)
    {       
            a=hash[0];
            b=hash[1];
            c=hash[2];
            d=hash[3];
            e=hash[4];
            f=hash[5];
            g=hash[6];
            h=hash[7];
            for(t=0;t<64;t++)
            {
                    if (t<=15)
                    {
                        W[t]=parsed_op[i][t];
                      
                    }
                    else
                    {
                        W[t]=SIG1(W[t-2])+W[t-7]+SIG0(W[t-15])+W[t-16];
                        
                    }
                    temp1=h+ EP1(e) + CH(e,f,g)+ k[t]+W[t]; 
                    temp2=EP0(a) + MAJ(a,b,c);
                    h=g;
                    g=f;
                    f=e;
                    e=d+temp1;
                    d=c;
                    c=b;
                    b=a;
                    a=temp1+temp2;
                                  
            }
            hash[0]+=a;
            hash[1]+=b;
            hash[2]+=c;
            hash[3]+=d;
            hash[4]+=e;
            hash[5]+=f;
            hash[6]+=g;
            hash[7]+=h;
        
    }
    printf("\n\n");
    for(i=0;i<8;i++)
    {
        printf("%x ",hash[i]);
    }
    printf("\n\n");
}
