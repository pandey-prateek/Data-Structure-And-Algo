#include <iostream>
#include <fstream>
#include <math.h>
#include <climits>

using namespace std;

void carve_seam_horizontal(int ***rgb,double** vp,double** gradient,int index,int j,int W){
    
    for(int i=j;i<W-1;i++){
        
        rgb[index][i]=rgb[index][i+1];
     
    }
}
void carve_seam_vertical(int ***rgb,int index,int j,int H){
    for(int i=j;i<H-1;i++){
        rgb[i][index]=rgb[i+1][index];
      
    }
}
void get_horizontal_path_carve(int ***rgb,double **hp,double **gradient,int H,int W){
    int  min_index;
    int index=W-1;
    double min_value=__DBL_MAX__;
    for(int i=0;i<H;i++){
        if(hp[i][W-1]<min_value){
            min_value=hp[i][W-1];
            min_index=i;
        }
    }

    int k=0;
    while(index>=0){
        carve_seam_vertical(rgb,index,min_index,H);
        index--;
        min_value=__DBL_MAX__;
        if(index>=0){
            
            if(min_index-1>=0){
                min_value=hp[min_index-1][index];   
                k=min_index-1;
            }
            if(hp[min_index][index]<min_value){
                min_value=hp[min_index][index];   
                k=min_index;
            }
            if(min_index+1<H&&hp[min_index+1][index]<min_value){
                min_value=hp[min_index+1][index];   
                k=min_index+1;
            }
            min_index=k;
        }
    }
    
}
void get_verticle_path_carve(int ***rgb,double **vp,double** gradient,int H,int W){
    int  min_index;
    int index=H-1;
    double min_value=__DBL_MAX__;
    for(int i=0;i<W;i++){
        if(vp[H-1][i]<min_value){
            min_value=vp[H-1][i];
            min_index=i;
        }
    }
    int k=0;

    while(index>=0){

        carve_seam_horizontal(rgb,vp,gradient,index,min_index,W);
        index--;
        min_value=__DBL_MAX__;
        if(index>=0){
            if(min_index-1>=0){
                min_value=vp[index][min_index-1];   
                k=min_index-1;
            }
            if(vp[index][min_index]<min_value){
                min_value=vp[index][min_index];   
                k=min_index;
            }
            if(min_index+1<W&&vp[index][min_index+1]<min_value){
                min_value=vp[index][min_index+1];   
                k=min_index+1;
            }
            min_index=k;
        }
    }
    
}
void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) {
   
    long long int Rx;
    long long int Ry;
    long long int Gx;
    long long int Gy;
    long long int Bx;
    long long int By;
 
    
        
    while(W_< W||H_<H){
        

        if(W_<W ){
            double **gradient=new double* [H]; 
    for(int i=0;i<H;i++){
        gradient[i]=new double[W];
        for(int j=0;j<W;j++){
            long long int Ex=0;
            long long int Ey=0;
            if(j==0){
                
                for(int k=0;k<C;k++){
                    Ex+=pow(rgb[i][j+1][k]-rgb[i][W-1][k],2);
                }
                
            }else{
                for(int k=0;k<C;k++){
                    Ex+=pow(rgb[i][(j+1)%W][k]-rgb[i][j-1][k],2);
                }
               
            }
            if(i==0){
                for(int k=0;k<C;k++){
                    Ey+=pow(rgb[i+1][j][k]-rgb[H-1][j][k],2);
                }
               
            }else{
                for(int k=0;k<C;k++){
                    Ey+=pow(rgb[(i+1)%H][j][k]-rgb[i-1][j][k],2);
                }
            }
            
            gradient[i][j]=sqrt(Ex+Ey);
            
        }
       
    }
        double **vp=new double* [H];

        for(int i=0;i<H;i++){
            vp[i]=new double[W];
            
        }
            for(int i=0;i<H;i++){
                for(int j=0;j<W;j++){
                    if(i==0){
                        vp[i][j]=gradient[i][j];
                        
                    }else{
                        vp[i][j]=__DBL_MAX__;
                        if(j-1>=0){
                            vp[i][j]=min(vp[i][j],gradient[i][j]+vp[i-1][j-1]);
                        }
                            vp[i][j]=min(vp[i][j],gradient[i][j]+vp[i-1][j]);
                        if(j+1<H){
                            vp[i][j]=min(vp[i][j],gradient[i][j]+vp[i-1][j+1]);
                        }
                        
                    }
                   // cout<<vp[i][j]<<" ";
                    

                  
                }
            }
            
            get_verticle_path_carve(rgb,vp,gradient,H,W);
    for(int i=0;i<H;i++){
        delete[] vp[i];
        delete[] gradient[i];
    }
    delete[] vp;
    delete[] gradient;
            W--;
    }
    if(H_<H){
        double **gradient=new double* [H]; 
    for(int i=0;i<H;i++){
        gradient[i]=new double[W];
        for(int j=0;j<W;j++){
            long long int Ex=0;
            long long int Ey=0;
            if(j==0){
                
                for(int k=0;k<C;k++){
                    Ex+=pow(rgb[i][j+1][k]-rgb[i][W-1][k],2);
                }
                
            }else{
                for(int k=0;k<C;k++){
                    Ex+=pow(rgb[i][(j+1)%W][k]-rgb[i][j-1][k],2);
                }
               
            }
            if(i==0){
                for(int k=0;k<C;k++){
                    Ey+=pow(rgb[i+1][j][k]-rgb[H-1][j][k],2);
                }
               
            }else{
                for(int k=0;k<C;k++){
                    Ey+=pow(rgb[(i+1)%H][j][k]-rgb[i-1][j][k],2);
                }
            }
            
            gradient[i][j]=sqrt(Ex+Ey);
            
        }
       
    }
        double **hp=new double* [H];

        for(int i=0;i<H;i++){
            hp[i]=new double[W];
            
        }
            for(int j=0;j<W;j++){
                for(int i=0;i<H;i++){
                    if(j==0){
                        hp[i][j]=gradient[i][j];
                    }else{
                        hp[i][j]=__DBL_MAX__;
                        if(i-1>=0){
                            hp[i][j]=min(hp[i][j],gradient[i][j]+hp[i-1][j-1]);
                        }
                            hp[i][j]=min(hp[i][j],gradient[i][j]+hp[i][j-1]);
                        if(i+1<H){
                            hp[i][j]=min(hp[i][j],gradient[i][j]+hp[i+1][j-1]);
                        }
                        

                    }
                
                  
                }
                
            }
            
            get_horizontal_path_carve(rgb,hp,gradient,H,W);
            H--;
    for(int i=0;i<H;i++){
        delete[] hp[i];
        delete[] gradient[i];
    }
    delete[] hp;
    delete[] gradient;
    }
    
       
    
   
    }
    
    
    
}

int main() {
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}