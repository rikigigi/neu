#include<neur.h>

collegamento::collegamento(perceptron * a, perceptron * b,float P){
    coll.push_back(a);
    coll.push_back(b);
    a->out.push_back(this);
    b->in.push_back(this);
    p=P;
}

int perceptron::collega_out(unsigned int N, perceptron **p,float *P){
    for (unsigned int i=0;i<N;i++){
        collegamento * t = new collegamento (this,p[i],P[i]);
    }
    return N;
}
int perceptron::collega_in(unsigned int N, perceptron **p,float *P){
    for (unsigned int i=0;i<N;i++){
        collegamento * t = new collegamento (p[i],this,P[i]);
    }
    return N;
}


int rete::set_in(float *input){
    for (unsigned int i=0;i<in.size();i++){
        in[i]->valore=input[i];
    }
}
int rete::get_out(float *output){
    for (unsigned int i=0;i<out.size();i++){
        output[i]=out[i]->valore;
        out[i]->valore=0.0; // azzero anche i perceptron di output
    }
}
int rete::run(){
    unsigned int c=0;
    vector<perceptron*> c1,c2;
    for (unsigned int i=0;i<in.size();i++){
        c1.push_back(in[i]);
    }
    while(c1.size()>0){
        c2.clear();
        for (unsigned int i=0;i<c1.size();i++){ // ciclo per i perceptron
            if (1){ // il perceptron si può attivare sempre
            c++;
            float v=(c1[i]->is_input)?(c1[i]->valore):(c1[i]->valore+c1[i]->soglia);
//			cout <<"c1["<<i<<"]="<<c1[i]<<" soglia="<< c1[i]->soglia <<" v="<<v<<" ";
                for (unsigned int j=0;j< c1[i]->out.size(); j++){ // ciclo su tutte le uscite
                    for (unsigned int jj=0;jj<c1[i]->out[j]->coll.size();jj++){ // ogni uscita può avere collegamenti multipli
                        if (c1[i]->out[j]->coll[jj] != c1[i]){ // se il puntatore è un altro perceptron
//							cout << "out["<<j<<"]->coll["<<jj<<"]="<<c1[i]->out[j]->coll[jj]<<" ";
                            if (c1[i]->out[j]->coll[jj]->mark==false) {
                                c2.push_back(c1[i]->out[j]->coll[jj]); // al prossimo giro di while devo usare anche questo perceptron // AH! NON DEVE ESSERE GIA' IN LISTA!
                                c1[i]->out[j]->coll[jj]->mark=true;
                            }
                            c1[i]->out[j]->coll[jj]->valore+=c1[i]->trasf(v)*c1[i]->out[j]->p; // aggiorno il valore del perceptron raggiunto
//							cout <<c1[i]->out[j]->p <<" ";
                        }
                    }
                }
            }
        }
        for (unsigned int i=0;i<c2.size();i++){
            c2[i]->mark=false;
        }
        c1.swap(c2);
    }
//		cout << "\n";
    for(unsigned int i=0;i<perc.size();i++) {
//		cout<< perc[i]->valore<<" ";
//		cout << perc[i]->valore<< " ";
        if(perc[i]->out.size()>0 && perc[i]->in.size()>0) { perc[i]->valore = 0.0;} // azzero il valore del perceptron se non è un perceptron terminale o iniziale
//		else {cout << perc[i]->valore <<" ";}
    }
//		cout << "\n==\n\n";

    return c;
}
int rete::feed_forward(unsigned int n_in, unsigned int n_out, unsigned int n_hidden, unsigned int hidden_layer){
    vector<perceptron*> ll1,ll2;
    float * pesi;
    init_cmwc4096();
    n_w=0;
    pesi=new float[n_in>n_out?(n_in>n_hidden?n_in:n_hidden):(n_out>n_hidden?n_out:n_hidden)];
    for (unsigned int i=0;i<n_in;i++){
        perceptron *t=new perceptron(tanh);
        perc.push_back(t);
        ll1.push_back(t);
        in.push_back(t);
        t->valore=0.0;
        t->soglia=0.0;
        t->is_input=true;
    }
    for (unsigned int j=0;j<hidden_layer;j++){
        for (unsigned int i=0;i<n_hidden;i++){
            // valori random fra -1 e 1 ai pesi
            for (unsigned int ii=0;ii<ll1.size();ii++) pesi[ii]=UNI;
            perceptron *t=new perceptron(tanh);
            perc.push_back(t);
            ll2.push_back(t);
            t->collega_in(ll1.size(),&ll1[0],pesi);
            n_w+=ll1.size()+1;
            t->valore=0.0;
            t->soglia=UNI;
            t->is_input=false;
        }
        ll1.swap(ll2);
        ll2.clear();
    }
    for (unsigned int i=0;i<n_out;i++){
        perceptron *t=new perceptron(tanh);
        perc.push_back(t);
        out.push_back(t);
        for (unsigned int ii=0;ii<ll1.size();ii++) pesi[ii]=UNI;
        t->collega_in(ll1.size(),&ll1[0],pesi);
            n_w+=ll1.size()+1;
        t->valore=0.0;
        t->soglia=UNI;
        t->is_input=false;
    }
    delete pesi;
}

float rete::E(float * ris) {
    float t=0;
    run();
    for (unsigned int i=0;i<out.size();i++){
        t+=(ris[i]-out[i]->valore)*(ris[i]-out[i]->valore);
        out[i]->valore=0.0; // azzero anche i perceptron di output
    }
    er=t/2.0;
    return er;
}

int rete::app_ff(unsigned int nmax,unsigned int nex,float**ex,float **ris,float inc=1e-4){
    float min=1e50,t1,e1,e2,p=1.0,incr=inc;
    float *dw=NULL;
    dw = new float[n_w];
    for (unsigned int i=0;i<n_w;i++) dw[i]=0;
    unsigned int cont;
//	cout << "================\n";
// gli input non devono avere la soglia!
    for (unsigned int n=0;n<nmax;n++){
        unsigned int ne=cmwc4096()%4;
        set_in(ex[ne]);
        cont=0;
        incr=inc*exp(-4.0*(float)n/(float)nmax);
        p=0.5*exp(-(float)n/(float)nmax);
        for (unsigned int i=0;i<perc.size();i++){
//				cout << "_____------______-\n";
                if (!perc[i]->is_input){
                    t1=perc[i]->soglia;
                    e1=E(ris[ne]);
                    perc[i]->soglia+=1e-5;
                    e2=E(ris[ne]);
                    dw[cont]=p*dw[cont]-incr*(e2-e1)/1e-5;
                    perc[i]->soglia=t1+dw[cont];
                    cont++;
                }
            for (unsigned int j=0;j<perc[i]->in.size();j++){
                t1=perc[i]->in[j]->p;
                e1=E(ris[ne]);
                perc[i]->in[j]->p+=1e-5;
                e2=E(ris[ne]);
                dw[cont]=p*dw[cont]-incr*(e2-e1)/1e-5;
                perc[i]->in[j]->p=t1+dw[cont];
                cont++;
            }
        }
    }
    delete dw;
}

int rete::ini_kohen(unsigned int nin,unsigned int nl, unsigned int n,unsigned int nout,unsigned int dim,float (*dist)(unsigned int*,float*)){
    float *pesi=new float[nin];
    for (unsigned int i=0;i<nin;i++){
         perceptron *t = new perceptron(tanh);
         perc.push_back(t);
         in.push_back(t);
         t->valore=0.0;
         t->soglia=0.0;
         t->is_input=true;
    }
    for (unsigned int i=0;i<pow(n,dim);i++){
        perceptron *t = new perceptron(tanh);
        perc.push_back(t);
        out.push_back(t);
        for (unsigned int ii=0;ii<in.size();ii++) pesi[ii]=UNI;
        t->collega_in(in.size(),&in[0],pesi);
    }
}

