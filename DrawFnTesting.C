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



void Draw(TTree* tree1, const char* filename2,  const char* pathName)
{


  // xxxxxxxxxxxx Get Binning Variables and Parameters from the CSV File xxxxxxxxxxxx //
  // xxxxxxxxxxxxxxxxxxxxxxxx Variables stored in an array Par[] xxxxxxxxxxxxxxxxxxxx //
  auto CSVfileName = "HistParameters.csv";
  auto df = ROOT::RDF::MakeCsvDataFrame(CSVfileName);

  TString SecondFile = filename2;
  TFile *f2 = TFile::Open(SecondFile.Data());
  f2->cd(path);
  
  TIter next(tree->GetListOfBranches());
  TKey *Key;
  while ((Key=(TKey*)next()))
    {            
      //TString TEMP="pt";
      TString BranchName=key->GetName();
      float* Par = GetParameters(df, BranchName.Data());
      int Bins = Par[0];
      float xMin = Par[1];
      float xMax = Par[2];
      
      TString Drawcmd1 = Form("%s>>hnew(%i,%f,%f)",BranchName.Data(),Bins,xMin,xMax);

      first_source->cd( path );
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
