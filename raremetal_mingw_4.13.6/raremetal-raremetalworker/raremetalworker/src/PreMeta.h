////////////////////////////////////////////////////////////////////// 
// PreMeta.cpp 
// (c) 2012-2013 Shuang Feng, Dajiang Liu, Goncalo Abecasis
// 
// This file is distributed as part of the RareMetalWorker source code package   
// and may not be redistributed in any form, without prior written    
// permission from the author. Permission is granted for you to       
// modify this file for your own personal use, but modified versions  
// must retain this copyright notice and must not be distributed.     
// 
// Permission is granted for you to use this file to compile RareMetalWorker.    
// 
// All computer programs have bugs. Use this file at your own risk.   
// 
// Wednesday November 28, 2012
// 

#ifndef __PREMETA_H__
#define __PREMETA_H__

#include "FastFit.h"
#include "VcfRecord.h"
#include "VcfFileReader.h"
#include "VcfHeader.h"
#include "InputFile.h"
#include "GroupFromAnnotation.h"
#include "DataQC.h"

class PreMeta
{
   public:
      PreMeta();
      ~PreMeta();

      static bool vcfAnnotated;
      static bool zipOutput;
      static bool checkRef;

      //Input/Output options	
      static String vcfInput;
      static String outputFile;
      static int Xstart,Xend;
      static String xLabel;
      static String dosageFlag;
      static bool dosage;
      static bool genoFromPed;
      static bool genoFromVCF;
      static bool FounderFreq;
      static bool correctGC;
      static int window;
      static int maleLabel;
      static int femaleLabel;
      static bool recessive;
      static bool dominant;
      static bool additive;
static bool calculateOR;

      int warnings;
      int numFounders;
      int malehwewarning;
      VcfFileReader reader;
      VcfHeader header;
      VcfRecord record;

      //this is the position of each marker in a gene for output
      int pos,hom1,het,hom2;
      double founderMaf,markerMaf,callRate;
      String chr,refAllele,rareAllele;
      double mac,hwe_pvalue;
      Eigen::VectorXf genotype, genotype_rec, genotype_dom;
      Eigen::VectorXf transGeno, transGeno_rec,transGeno_dom;
      Vector residuals;
      Vector  chisq_before_GCcorrect_rec, chisq_before_GCcorrect_dom, chisq_before_GCcorrect;
      Vector pvalueAll,pvalueAll_rec,pvalueAll_dom;
      Vector pos_plot,pos_plot_rec,pos_plot_dom;
      StringArray chr_plot,chr_plot_rec,chr_plot_dom;
      Vector maf_GC,maf_GC_rec,maf_GC_dom;
      IFILE SCOREoutput,SCOREoutput_rec,SCOREoutput_dom;
      IFILE SCOREcov,SCOREcov_rec,SCOREcov_dom;

      Vector chisqred;
      double lambda;
      Matrix projectionMat,inv;

      void CalculateProjectionMatrix(FastTransform & trans,FastFit & engine,Vector & sigma2);

      void Run(IFILE SCOREoutput, IFILE SCOREoutput_rec,IFILE SCOREoutput_dom, IFILE SCOREcov, IFILE SCOREcov_rec,IFILE SCOREcov_dom,Pedigree & ped, FastTransform & trans,FastFit & engine,GroupFromAnnotation & group, FILE * log,SanityCheck & checkData,KinshipEmp & kin_emp);
      void VCFSanityCheck();
      bool GetGenotypeVectorVCFDosage(FastTransform & trans, Pedigree & ped);
      bool GetGenotypeVectorVCF(FastTransform & trans, Pedigree & ped,SanityCheck & checkData,FILE * log);
      int GetGenotypeVectorPED(FastTransform & trans, Pedigree & ped,int markerid,FILE *log);
      //bool GetGenotypeVector(FastTransform & trans, Pedigree & ped,int markerid);
      void PrintHeader(IFILE output,FastFit & engine,FastTransform & trans,Pedigree & ped);
      double CalculateCov(FastFit & engine,FastTransform & trans, Pedigree & ped, Matrix & genotypeAl,Vector & sigma2,int m);

      void CalculateUnrelatedAssocStats(double & effSize,double & pvalue, double & chisq, double & numerator,double & denominator, Eigen::VectorXf & genotype,FastFit & engine,FastTransform & trans,Vector & sigma2);
      void CalculateAssocStats(double & effSize,double &pvalue,double &numerator,double &denominator,double &chisq, Eigen::VectorXf & transGeno,FastFit & engine,FastTransform & trans,Vector & sigma2);

      void RelatedAssoc(IFILE SCOREoutput, IFILE SCOREoutput_rec,IFILE SCOREoutput_dom, Pedigree & ped,FastFit & engine,FastTransform & trans,Vector & sigma2);

      void UnrelatedAssoc(IFILE SCOREoutput, IFILE SCOREoutput_rec,IFILE SCOREoutput_dom, Pedigree & ped,FastFit & engine,FastTransform & trans,Vector & sigma2);

      void GeneratePlots(String & filename,Vector & pvalueAll,StringArray & chr_plot,Vector & pos_plot,GroupFromAnnotation & group,IFILE & SCOREoutput,Vector & chisq_before_GCcorrect,Vector & maf_GC,String & model);
void GetRealPrefix(String & file);
};

#endif
