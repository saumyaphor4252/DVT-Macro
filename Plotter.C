void Recursion(TDirectory* , const char*, const char*); 

void Comparing_2_Files(const char* fileName1, const char* fileName2)
{
  TString InputFile = Form("%s",fileName1);
  TFile *file=new TFile(InputFile.Data());
  TString target1=file->GetPath();
  gSystem->Exec("mkdir Plots");
  
  file->GetListOfKeys()->Print();
  Recursion(file, fileName1, fileName2);  
}

void Recursion(TDirectory* target, const char* filename1, const char* filename2)
{
  TFile *f1=TFile::Open( filename1, "r" );
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );
  f1->cd(path);
  TDirectory *temp= gDirectory;
    
  TIter next(temp->GetListOfKeys());
  TKey *key;
  while ((key=(TKey*)next()))
    {
      TObject *obj = key->ReadObj();
      // xxxxxxxxxxxxxxxxxxxx If the TObject is a TDirectory xxxxxxxxxxxxxxxxxxxxxxxxxxx //
      if ( obj->IsA()->InheritsFrom( TDirectory::Class()))
	{
	  std::cout << "Found subdirectory " << obj->GetName() <<std::endl;
	  TDirectory *subdir = (TDirectory*)obj;
	  std::cout<<subdir->GetPath()<<std::endl;
	  Recursion( subdir ,  filename1, filename2);
	}
      // xxxxxxxxxxxxxxxxxxxx If the TObject is a TH1 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx //
      else if (obj->IsA()->InheritsFrom( TH1::Class() ))
	{	  
	  TH1F *h1 = (TH1F*)obj;
	  TDirectory *HistDir = histogram1->GetDirectory();
	  TString DirPath( (char*)strstr( HistDir->GetPath(), ":" ) );
	  DirPath.Remove( 0, 2 );
	  
          TFile *file2=TFile::Open( filename2, "r" );
	  TString HistName = key->GetName();
	  TString cmd2 = DirPath+"/"+HistName;
          TH1F *h2 = (TH1F*)file2->Get(cmd2.Data());		      
	  
	  TCanvas c("c","c",800,600); 
	  h1->SetLineColor(kBlue);
	  h1->SetLineWidth(3);
	  h1->DrawNormalized();
	  h2->SetLineColor(kRed);
	  h2->SetLineWidth(3);
	  h2->DrawNormalized("Same");
 	  
	  TString PNGname = treeName + "_" + BranchName + ".png";
	  c.SaveAs(PNGname.Data());
	  TString cmd4 = "mv  " + PNGname + "  Plots";
	  gSystem->Exec(cmd4.Data());
	  
	  c.Clear();    
	  h1->Clear();
	  h2->Clear();	  
	}	            
      else
	{ std::cout<<"The class is not a TDirectory or TH1 !"<<std::endl;         
	}
      
    } // while loop
  
} //Recursion Function


