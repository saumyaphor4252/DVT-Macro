float* GetParameters(ROOT::RDataFrame df, TString var)
{


   static float HistPar[3]; 
  
 
   TString cmd = "Variable == \""+ var+ "\"";
   auto filteredEvents = df.Filter(cmd.Data());
   auto bins = filteredEvents.Take<Long64_t>("Bins");
   auto xMin = filteredEvents.Take<double>("Xmin");
   auto xMax = filteredEvents.Take<double>("Xmax");
   // auto d2=df.Display("",-1);
   // d2->Print();
   //std::cout<<" Type of bins : "<<type(bins)<<std::endl;
   std::cout<<"Bins value is: "<<bins->at(0)<<std::endl;
   std::cout<<"xMin value is: "<<xMin->at(0)<<std::endl;
   std::cout<<"xMax is: "<<xMax->at(0)<<std::endl;
   HistPar[0]=bins->at(0); 
   HistPar[1]=xMin->at(0);
   HistPar[2]=xMax->at(0);
   /* std::cout<<HistPar[0]<<std::endl;
   std::cout<<HistPar[1]<<std::endl;
   std::cout<<HistPar[2]<<std::endl;
   */  bins->clear();
   xMin->clear();
   xMax->clear();
   return HistPar;
   
}



void GetDF(TString TEMP)
{
  auto fileName = "HistParameters.csv";
  auto df = ROOT::RDF::MakeCsvDataFrame(fileName);
  //TString TEMP="pt";
  float* Par = GetParameters(df, TEMP);
  std::cout<<Par[0]<<std::endl;
  std::cout<<Par[1]<<std::endl;
  std::cout<<Par[2]<<std::endl;
  
  
}


int main()
{
  int  counter =0;
  TString TEMP;
  for(int i=0 ;i<3 ;i++)
    {
      if(counter ==0)
	{TEMP="pt";
	}
      else if(counter==1)
	{TEMP="charge";
	   }
       else if(counter==2)
	 {TEMP="phi";
	   }      
     
      GetDF(TEMP);
      counter++;
    }
  
}

 // auto d2 = df.Display({"Variable", "Bins"});
