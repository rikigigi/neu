#ifndef NEUR_H
#define NEUR_H




#include <vector>
#include <cmath>
#include <stdint.h>
#include <iostream>
#include <eigen3/Eigen/Dense>


//*****************************************
// esponenziale per due punti a*exp(-b*x)
//*****************************************
static float expa(float x1,float x2,float y1, float y2){
    return exp(((x1/x2)*log(y2)-log(y1))/(x1/x2-1));
}

static float expb(float x1,float x2,float y1, float y2){
    return ((x1/x2)*log(y2)-log(y1))/(x1*(x1/x2-1)) -log(y1)/x1;
}

//*****************************************
// varie funzioni per numeri pseudo-casuali
//*****************************************

#define SHR3 (jz=jsr, jsr^=(jsr<<13), jsr^=(jsr>>17), jsr^=(jsr<<5),jz+jsr)
//#define UNI (rnd_single()-0.75)*4.0
#define UNI (rnd_single()-0.75)*200
// array di stato dei generatori, globale
static uint32_t Q_[4096], jz,jsr=123;


static void init_cmwc4096(){
int i;
        for (i=0;i<4096;i++){
                Q_[i]=SHR3;
        }
}

// questa funzione genera un numero intero pseudo-casuale a 32 bit (compreso fra 0 e 2^32-1) -- algoritmo di Marsaglia
static uint32_t cmwc4096(){
uint64_t t, a=18782LL;
static uint32_t i=4095,c_=362436;
uint32_t x,r=0xfffffffe;
        i=(i+1)&4095;
        t=a*Q_[i]+c_;
        c_=(t>>32);
        x=t+c_;
        if(x<c_){
                x++;c_++;
        }
        return(Q_[i]=r-x);
}

/*
// questa funzione combina due numeri interi a 32 bit in un numero intero a 64 bit, usando le operazioni fra bit.
static uint64_t rnd64(void){
uint64_t r=0;
r=( ( (uint64_t) cmwc4096() << 32 )& 0xFFFFFFFF00000000ull) | ( (uint64_t) cmwc4096() & 0x00000000FFFFFFFFull); // << sposta i bit a sinistra della quantita' intera specificata. | esegue un "or" bit per bit, & "and"
return r;
}

// prende direttamente i bit da un numero intero casuale e li mette dentro la mantissa del numero float, impostando anche l'esponente. Il numero generato e' compreso fra 0.5 e 1 (il numero e' scritto in base 2).
static double rnd_double() {
double t;
uint64_t r;
uint32_t rr;
        if (sizeof(double)==8) { // float a 64 bit
                r=rnd64();
//                            001111111110=0x3FE
                r= (r>>12)& 0x000FFFFFFFFFFFFFull  | 0x3FE0000000000000ull;
                t= * (double*) &r;
        }else if (sizeof(double)==4) { // float a 32 bit
                rr=cmwc4096();
//                            001111110000 = 0x3F000000
                rr=(rr>>9)& 0b00000000011111111111111111111111 | 0x3F000000;
                t=*(double*)&rr;
        } else {
//               printf (fstderr,"Errore: tipo double non riconosciuto.\n");
        }
return t;
}
*/
// stessa cosa con il tipo a 32 bit
static float rnd_single() {
uint32_t r;
float t;
        if (sizeof(float)==4){
                r=cmwc4096();
//                          001111110000
                r=(r>>9)& 0b00000000011111111111111111111111 | 0x3F000000;
                t=*(float*)&r;
        } else {
//                fprintf(stderr,"Errore: tipo float non riconosciuto.\n");
        }
return t;
}




using namespace std;
using namespace Eigen;



class perceptron;

class collegamento {
    public:
    float p;
    vector<perceptron*> coll;
    collegamento(perceptron * a, perceptron * b,float P);
    ~collegamento(){/*
        // rimuovi i collegamenti dai perceptron. Se il perceptron aveva solo questo collegamento come input o come output eliminalo
        for (unsigned int i=0;i<a->out.size();i++){
            if (a->out[i]==this){ // rimuovi l'elemento del vector
            }
        }
        for (unsigned int i=0;i<a->in.size();i++){
            if (a->in[i]==this){
            }
        }
        // libera la memoria
        coll.clear();*/
    }
};

class perceptron {
    public:
    bool mark,is_input;
    vector<collegamento*> in;
    vector<collegamento*> out;
    float soglia;
    float valore;
    int collega_out(unsigned int N,perceptron ** p,float * P);
    int collega_in(unsigned int N,perceptron ** p,float * P);
    float (*trasf)(float);
    unsigned int *coord;
    perceptron(float (*tr)(float)){
        trasf=tr;
        valore=0.0;
        mark=false;
    }
    ~perceptron(){
        //rimuove i collegamenti, eliminando l'oggetto se ci sono solo due perceptron collegati
        for (unsigned int i=0;i<in.size();i++){
            if (in[i]->coll.size()<=2) {
                delete in[i];
            } else {
                for (unsigned int j=0;j<in[i]->coll.size();j++){
                    if (in[i]->coll[j]==this){ // rimuovi l'elemento del vector
                    }
                }
            }
        }
        for (unsigned int i=0;i<out.size();i++){
            if (out[i]->coll.size()<=2) {
                delete out[i];
            } else {
                for (unsigned int j=0;j<out[i]->coll.size();j++){
                    if (out[i]->coll[j]==this){ // rimuovi l'elemento del vector
                    }
                }
            }
        }
        //libera la memoria
        in.clear();
        out.clear();
    }
    private:
};

class rete {
public:
vector<perceptron*> perc;
vector<perceptron*> in;
vector<perceptron*> out;
unsigned int n_w;
int set_in(float *input);
int get_out(float *output);
int run();
int feed_forward(unsigned int n_in, unsigned int n_out, unsigned int n_hidden, unsigned int hidde_layer);
float E(float * ris);
float er;
int app_ff(unsigned int nmax,unsigned int nex,float**ex,float **ris,float inc);
float (*dist)(unsigned int*,float *); // distanza fra neuroni
int ini_kohen(unsigned int nin,unsigned int nl, unsigned int n,unsigned int nout,unsigned int dim,float (*dist)(unsigned int*,float*));
private:
};

// potenze intere di interi
template <unsigned int n,unsigned int ex> struct intpower{
    enum {value = n*intpower<n,ex-1>::value};
};
template <unsigned int n> struct intpower<n,0>{
    enum {value = 1};
};

//potenze intere di reali
template <typename T,unsigned int n> class power {
public:
    static inline T p(T t){
        return power<T,n-1>::p(t)*t;
    }
};
template <typename T> class power<T,0> {
public:
    static inline T p(T t){
        return 1.0;
    }
};

// gaussiana n-D

template <unsigned int n> class g_nD {
public:
    static inline float S(float *pos,float param){
        return pos[n]*pos[n]/param+g_nD<n-1>::G(pos,param);
    }
    static inline float G(float *pos,float param){
        return exp(S(pos,param));
    }
};

template<> class g_nD<0>{
public:
    static inline float S(float *pos,float param){
        return pos[0]*pos[0]/param;
    }
    static inline float G(float *pos,float param){
        return exp(S(pos,param));
    }
};




template <unsigned int N> class infomax {
    public:
    unsigned int n;
    Matrix <float,N,N> W,dW;
    Matrix <float,N,1> w0,dw0;
    Matrix <float,N,1> x,y,uno;
    infomax();
    void set_in(float *);
    void get_out(float *);
    void app(unsigned int);
    void run();
};

template <unsigned int N>infomax<N>::infomax(){
    n=N;
    for (unsigned int i=0;i<N;i++) {
        w0(i)=UNI;
        uno(i)=1.0;
        for (unsigned int j=0;j<N;j++){
            W(i,j)=UNI;
        }
    }
}

template <unsigned int N> void infomax<N>::run(){
    Matrix <float,N,1> t;
    t=W*x+w0;
    for (unsigned int i=0;i<n;i++) y(i) = 1.0/(1+exp(-t(i)));
}

template <unsigned int N> void infomax<N>::app(unsigned int na){
    for (unsigned int c=0;c<na;c++){
        dw0=uno-2*y;
        dW=W.transpose().inverse()+dw0*x.transpose();
    }
}

template <unsigned int N> void infomax<N>::set_in(float * in) {
    for (unsigned int i=0;i<n;i++){
        x(i)=in[i];
    }
}

template <unsigned int N> void infomax<N>::get_out(float *out) {
    for (unsigned int i=0;i<n;i++){
        out[i]=y(i);
    }
}


template <unsigned int nin, unsigned int n, unsigned int dim>class kohonen{
public:
    Matrix <float, intpower<n,dim>::value,nin> W;
    Matrix <float, intpower<n,dim>::value,nin> dW;
    Matrix <float,nin,Dynamic> in;
    Matrix <float,intpower<n,dim>::value,dim> pos;
    float (*dist)(float*,float);
    kohonen(float(*d)(float*,float)=NULL);
    void add_input(float* I);
    void remove_input(const unsigned int &idx);
    void run(const unsigned int&, const float &,const float&);
};

template<unsigned int nin,unsigned int n, unsigned int dim,unsigned int row,unsigned int i> class norma_quadra {
public:
    static inline float N(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,const unsigned int &ii){
        return power<float,2>::p((*W)(row,i)-(*in)(i,ii))+norma_quadra<nin,n,dim,row,i-1>::N(W,in,ii);
    }
};
template<unsigned int nin,unsigned int n, unsigned int dim,unsigned int row> class norma_quadra<nin,n,dim,row,0> {
public:
    static inline float N(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,const unsigned int &ii){
        return power<float,2>::p((*W)(row,0)-(*in)(0,ii));
    }
};

//trova il minimo fra le distanze al quadrato
template<unsigned int nin,unsigned int n,unsigned int dim,unsigned int i> class min_dist{
public:
    static inline void M(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,float *min,unsigned int *idx,const unsigned int &ii){
        float t=norma_quadra<nin,n,dim,i,nin-1>::N(W,in,ii);
        if ( t  < *min) {*idx=i;*min=t;}
        min_dist<nin,n,dim,i-1>::M(W,in,min,idx,ii);
    }
};
template<unsigned int nin,unsigned int n,unsigned int dim> class min_dist<nin,n,dim,0>{
public:
    static inline void M(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,float *min,unsigned int *idx,const unsigned int &ii){
        if ( norma_quadra<nin,n,dim,0,nin-1>::N(W,in,ii)  < *min) *idx=0;
    }
};

// base per la "distanza" fra neuroni in base all'indice
template<unsigned int n,unsigned int di,unsigned int idx1> class idx_to_dist{
public:
    static inline void D(float * d,const unsigned int &idx2){
        d[di]=(float)((int)((idx1/intpower<n,di>::value)%n) - (int)((idx2/intpower<n,di>::value)%n));
        idx_to_dist<n,di-1,idx1>::D(d,idx2);
    }
};
template<unsigned int n,unsigned int idx1> class idx_to_dist<n,0,idx1>{
public:
    static inline void D(float * d,const unsigned int &idx2){
        d[0]=(float)((int)(idx1%n) - (int)(idx2%n));
    }
};

//moltiplica un riga per una costante
template <unsigned int nin,unsigned int n,unsigned int dim,unsigned int row,unsigned int col> class row_mult{
public:
    static inline void M(Matrix <float,intpower<n,dim>::value,nin> *dW,float v){
        (*dW)(row,col)=(*dW)(row,col)*v;
        row_mult<nin,n,dim,row,col-1>::M(dW,v);
    }
};
template <unsigned int nin,unsigned int n,unsigned int dim,unsigned int row> class row_mult<nin,n,dim,row,0>{
public:
    static inline void M(Matrix <float,intpower<n,dim>::value,nin> *dW,float v){
        (*dW)(row,0)=(*dW)(row,0)*v;
    }
};

// modifica i pesi dei neuroni in base al vincitore
template<unsigned int nin,unsigned int n,unsigned int dim,unsigned int i,unsigned int j> class appr_vinc{
public:
    static inline void A(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,Matrix <float, intpower<n,dim>::value,nin> *dW,unsigned int vinc_idx,float (*dist)(float*,float),const float &k,const unsigned int &ii){
        //float w_ij=(*W)(i,j);
        // peso di prima + una costante(che poi varierà con le iterazioni) * coefficiente che dipende dalla distanza dal peso * funzione che pesa la distanza dal neurone vincitore
        (*dW)(i,j)=((*in)(j,ii)-(*W)(i,j));
        appr_vinc<nin,n,dim,i,j-1>::A(W,in,dW,vinc_idx,dist,k,ii);
    }
};
template<unsigned int nin,unsigned int n,unsigned int dim,unsigned int i> class appr_vinc<nin,n,dim,i,0>{
public:
    static inline void A(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,Matrix <float, intpower<n,dim>::value,nin> *dW,unsigned int vinc_idx,float (*dist)(float*,float),const float &k,const unsigned int &ii){
        //float w_ij=(*W)(i,j);
        // peso di prima + una costante(che poi varierà con le iterazioni) * coefficiente che dipende dalla distanza dal peso * funzione che pesa la distanza dal neurone vincitore
        (*dW)(i,0)=((*in)(0,ii)-(*W)(i,0));
        // moltiplica per il peso la riga
        float dp[dim];
        idx_to_dist<n,dim-1,i>::D(dp,vinc_idx);
        //(*dW).row(i)*=dist(dp,k);
        row_mult<nin,n,dim,i,nin-1>::M(dW,dist(dp,k));
        appr_vinc<nin,n,dim,i-1,nin-1>::A(W,in,dW,vinc_idx,dist,k,ii);
    }
};
template<unsigned int nin,unsigned int n,unsigned int dim> class appr_vinc<nin,n,dim,0,0>{
public:
    static inline void A(Matrix <float, intpower<n,dim>::value,nin> *W,Matrix <float,nin,Dynamic> *in,Matrix <float, intpower<n,dim>::value,nin> *dW,unsigned int vinc_idx,float (*dist)(float*,float),const float &k,const unsigned int &ii){
        //float w_ij=(*W)(i,j);
        // peso di prima + una costante(che poi varierà con le iterazioni) * coefficiente che dipende dalla distanza dal peso * funzione che pesa la distanza dal neurone vincitore
        (*dW)(0,0)=((*in)(0,ii)-(*W)(0,0));
        // moltiplica per il peso la riga
        float dp[dim];
        idx_to_dist<n,dim-1,0>::D(dp,vinc_idx);
        row_mult<nin,n,dim,0,nin-1>::M(dW,dist(dp,k));
        //(*dW).row(0)*=dist(dp,k);
    }
};

//apprendi con gli esempi dati
template<unsigned int nin,unsigned int n,unsigned int dim> void kohonen<nin,n,dim>::run(const unsigned int &cicli, const float &e, const float &k){
    if (in.cols()<=0 || cicli == 0) return;
    for (unsigned int c=0;c<cicli;c++){

        for (unsigned int ii=0;ii<in.cols();ii++){
            unsigned int i=cmwc4096()%in.cols();
            float min=1e10;
            unsigned int win=0;
            min_dist<nin,n,dim,intpower<n,dim>::value-1>::M(&W,&(in),&min,&win,i);
            //adesso che so chi è il vincitore devo farlo apprendere
            appr_vinc<nin,n,dim,intpower<n,dim>::value-1,nin-1>::A(&W,&(in),&dW,win,dist,e,i);
            W=W+k*dW;
        }
    }
}

// per inizializzare i pesi dei neuroni a valori pseudo-casuali
// i deve partire da n^dim-1, j da nin-1
template <unsigned int n,unsigned int dim,unsigned int nin,int i,int j> class rnd_mat {
public:
    static inline void inizializza(Matrix<float,intpower<n,dim>::value,nin> * mat){
        (*mat)(i,j)=UNI;
        rnd_mat<n,dim,nin,i,j-1>::inizializza(mat);
    }
};
template <unsigned int n,unsigned int dim,unsigned int nin> class rnd_mat<n,dim,nin,0,-1>{
public:
    static inline void inizializza(Matrix<float,intpower<n,dim>::value,nin>*mat){
        //(*mat)(0,0)=UNI;
    }
};

template <unsigned int n,unsigned int dim,unsigned int nin,int i> class rnd_mat<n,dim,nin,i,-1>{
public:
    static inline void inizializza(Matrix<float,intpower<n,dim>::value,nin>*mat){
        //(*mat)(i,0)=UNI;
        rnd_mat<n,dim,nin,i-1,nin-1>::inizializza(mat);
    }
};


//per inizializzare la matrice delle coordinate dei neuroni
//i deve partire da n-1
template <typename T,unsigned int n,unsigned int dim,unsigned int ini,unsigned int m, unsigned int i> class iniz {
public:
    static inline void inizializza(Matrix<T,intpower<n,dim>::value,dim> * mat){
        for(unsigned int ii=0;ii<intpower<n,m-1>::value;ii++){
            (*mat)(ii+i*intpower<n,m-1>::value+ini,m-1)=(T)i;
        }
        iniz<T,n,dim,ini+i*intpower<n,m-1>::value,m-1,n-1>::inizializza(mat);
        iniz<T,n,dim,ini,m,i-1>::inizializza(mat);
    }
};

template <typename T,unsigned int n,unsigned int dim,unsigned int ini,unsigned int m> class iniz<T,n,dim,ini,m,0>{
public:
    static inline void inizializza(Matrix<T,intpower<n,dim>::value,dim> * mat){
        for(unsigned int ii=0;ii<intpower<n,m-1>::value;ii++){
            (*mat)(ii+ini,m-1)=(T)0;
        }
        iniz<T,n,dim,ini,m-1,n>::inizializza(mat);
    }
};

template <typename T,unsigned int n,unsigned int dim,unsigned int ini,unsigned int i> class iniz<T,n,dim,ini,1,i>{
public:
    static inline void inizializza(Matrix<T,intpower<n,dim>::value,dim> * mat) {
        for (unsigned int ii=0;ii<n;ii++){
            (*mat)(ii+ini,0)=(T)ii;
        }
    }
};
template <unsigned int nin,unsigned int n,unsigned int dim> kohonen<nin,n,dim>::kohonen(float(*d)(float*,float)){
    if(d==NULL){
        dist=g_nD<dim-1>::G;
    }else{
        dist=d;
    }
    iniz<float,n,dim,0,dim,n-1>::inizializza(&pos);
    rnd_mat<n,dim,nin,intpower<n,dim>::value-1,nin-1>::inizializza(&W);
    in.resize(nin,0);
}

template <unsigned int nin,unsigned int n> class array_assign{
public:
    static inline void A(Matrix <float,nin,Dynamic> *in, float *I,unsigned int col){
        (*in)(n,col)=I[n];
        array_assign<nin,n-1>::A(in,I,col);
    }
};

template <unsigned int nin> class array_assign<nin,0>{
public:
    static inline void A(Matrix <float,nin,Dynamic> *in,float *I, unsigned int col){
        (*in)(0,col)=I[0];
    }
};

template <unsigned int nin,unsigned int n,unsigned int dim> void kohonen<nin,n,dim>::add_input(float *I){
    in.conservativeResize(in.rows(),in.cols()+1);
    array_assign<nin,nin-1>::A(&in,I,in.cols()-1);
}

template <unsigned int nin,unsigned int n,unsigned int dim> void kohonen<nin,n,dim>::remove_input(const unsigned int &idx){
    in.col(idx)=in.col(in.cols()-1);
    in.conservativeResize(in.rows(),in.cols()-1);
}



#endif // NEUR_H
