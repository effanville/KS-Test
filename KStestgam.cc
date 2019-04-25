#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>


double EmpDist(std::vector<double> V ,double x)
{
    double n=0;
    int i=0;
    //std::cout <<"eval pt "<< x <<" size of vector "<<V.size()<<'\n';
    for(i=0;i<V.size();i++)
    {
        if(V[i]<=x)
        {
            n++;
        }
    }
    double ans=0;
    ans=n/V.size();
    //std::cout<< "number less "<< n<<'\n';
    //std::cout << "density "<<ans<<'\n';
    return ans;
}
double 

double KSval(std::vector<double> V1, double m , double s)
{
    int i=0;
    
    std::vector<double> Val(V1.size());
    
    for(i=0;i<V1.size();i++)
    {   
        Val[i]=std::abs(EmpDist(V1,V1[i])-norcdf(m,s,V1[i]));
        //std::cout<<Val[i]<<'\n';
    }
    double max=0;
    for(i=0;i<Val.size();i++)
    {
        if(Val[i]>=max)
        {
            max=Val[i];
        }
    }
    return max;
}

int main()
{
    std::vector<double> Samp1;
    
    std::ifstream sample1;
    sample1.open("sample1.txt",std::ios::in);
    if (!sample1) 
    {//ensures that the file can indeed be opened.
        std::cout << "==============================================================="<<'\n';
		std::cout << " Unable to open file sample1.txt" << '\n';
        std::cout << " Therefore we are closing the program." << '\n';
        std::cout << " " <<'\n';
        std::cout << " The user should be aware that there must be a file called "<<'\n';
        std::cout << " sample1.txt in the same directory as the program for " <<'\n';
        std::cout << " the program to work. Maybe create a file and try again?"<<'\n';
        std::cout << "==============================================================="<<'\n';
		return 0;
    }
    
    while(sample1.good())
    {
        std::string line;
        getline(sample1,line);
        double m=0;
        std::stringstream liner(line);
        while(liner >>m)
        {
            if(m!=0)
            {
                Samp1.push_back(m);
            }
        }
    }
    sample1.close();
    
    double mu=0;
    double s=1;
    std::cout << " Gamma alpha"<<'\n';
    std::cin >> mu;
    std::cout << " Gamma beta"<<'\n';
    std::cin >> s;
    
    std::cout << "Sample 1 size " << Samp1.size()<<'\n';
    
    std::gamma_distribution<> distribution(mu,s);
    
    std::cout << " K-S Value "  <<KSval(Samp1, mu, s)<< '\n';
    
    std::cout << " outputting empirical plots"<<'\n';
    std::ofstream empirical;
    empirical.open("output.txt",std::ios::out);
    double xval=0;
    bool ending=false;
    while(!ending)
    {
        empirical<<xval <<" " << EmpDist(Samp1, xval)<< " "<<GD(xval)<< '\n';
        xval+=0.1;
        if((EmpDist(Samp1, xval)==1)&&(GD(xval)==1))
        {   
            ending =true;
        }
    }
    empirical.close();
    
    return 0;
}
