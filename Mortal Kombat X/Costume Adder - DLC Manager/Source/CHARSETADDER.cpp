#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream fin,listf;
    ofstream fout;
    char c;
    char *nameShort;
    string CHARname,type,relief,ch;

    listf.open("name2.txt");
    fin.open("Extract/$StartupCacheDir$/Config/X64-MK10Game.ini");
    fin>>noskipws;
    fout.open("Modded.ini");
    while (fin>>c)
        fout<<c;
    fout<<endl;

    while(getline(listf,CHARname))
    {
        fout<<endl;
        fout<<"[CharacterSettings.CHAR_"<<CHARname<<"]"<<endl;
        fout<<"MeshName=Meshes."<<CHARname<<endl;
        fout<<"Dismemberment=DISM_";

        nameShort = new char[3];
        //Taking name as size of 3 to easily tell characters apart and be able to compare them easily too.
        for (int i = 0; i < 3; i++)
        {
            nameShort[i]=toupper(CHARname[i]);
        }

        cout<<nameShort<<" "<<strlen(nameShort);

        if (nameShort == string("AZT"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Aztec_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Aztec_Mic"<<endl;
                fout<<"Trait=TRAIT_Aztec1"<<endl;
                fout<<"Trait=TRAIT_Aztec2"<<endl;
                fout<<"Trait=TRAIT_Aztec3"<<endl;

            } else

        if (nameShort == string("CAG"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Cassie_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Cassie_Mic"<<endl;
                fout<<"Trait=TRAIT_CageJr1"<<endl;
                fout<<"Trait=TRAIT_CageJr2"<<endl;
                fout<<"Trait=TRAIT_CageJr3"<<endl;

            } else

        if (nameShort == string("GOR"))
            {
                fout<<"ShokanMale"<<endl;
                fout<<"Dismemberment=DISM_ShokanMale_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Goro_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Goro_Mic"<<endl;
                fout<<"Trait=TRAIT_Goro1"<<endl;
                fout<<"Trait=TRAIT_Goro2"<<endl;
                fout<<"Trait=TRAIT_Goro3"<<endl;

            } else

        if (nameShort == string("JAX"))
            {
                if (CHARname.length()>6)
                {

                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Jacqui_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Jacqui_Mic"<<endl;
                fout<<"Trait=TRAIT_JaxJr1"<<endl;
                fout<<"Trait=TRAIT_JaxJr2"<<endl;
                fout<<"Trait=TRAIT_JaxJr3"<<endl;

                } else
                {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Jax_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Jax_Mic"<<endl;
                fout<<"Trait=TRAIT_Jax1"<<endl;
                fout<<"Trait=TRAIT_Jax2"<<endl;
                fout<<"Trait=TRAIT_Jax3"<<endl;


                }

            } else

        if (nameShort == string("KIT"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Kitana_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Kitana_Mic"<<endl;
                fout<<"Trait=TRAIT_Kitana1"<<endl;
                fout<<"Trait=TRAIT_Kitana2"<<endl;
                fout<<"Trait=TRAIT_Kitana3"<<endl;

            } else

        if (nameShort == string("LAD"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_DVorah_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_DVorah_Mic"<<endl;
                fout<<"Trait=TRAIT_LadyBug1"<<endl;
                fout<<"Trait=TRAIT_LadyBug2"<<endl;
                fout<<"Trait=TRAIT_LadyBug3"<<endl;

            } else

        if (nameShort == string("MAS"))
            {
                fout<<"MasterMale"<<endl;
                fout<<"Dismemberment=DISM_MasterMale_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_FerraTorr_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_FerraTorr_Mic"<<endl;
                fout<<"Trait=TRAIT_MasterMale1"<<endl;
                fout<<"Trait=TRAIT_MasterMale2"<<endl;
                fout<<"Trait=TRAIT_MasterMale3"<<endl;

            } else

        if (nameShort == string("MIL"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Mileena_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Mileena_Mic"<<endl;
                fout<<"Trait=TRAIT_Mileena1"<<endl;
                fout<<"Trait=TRAIT_Mileena2"<<endl;
                fout<<"Trait=TRAIT_Mileena3"<<endl;

            } else

        if (nameShort == string("QUA"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_QuanChi_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_QuanChi_Mic"<<endl;
                fout<<"Trait=TRAIT_QuanChi1"<<endl;
                fout<<"Trait=TRAIT_QuanChi2"<<endl;
                fout<<"Trait=TRAIT_QuanChi3"<<endl;

            } else

        if (nameShort == string("RAI"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Raiden_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Raiden_Mic"<<endl;
                fout<<"Trait=TRAIT_Raiden1"<<endl;
                fout<<"Trait=TRAIT_Raiden2"<<endl;
                fout<<"Trait=TRAIT_Raiden3"<<endl;

            } else

        if (nameShort == string("SON"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Sonya_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Sonya_Mic"<<endl;
                fout<<"Trait=TRAIT_Sonya1"<<endl;
                fout<<"Trait=TRAIT_Sonya2"<<endl;
                fout<<"Trait=TRAIT_Sonya3"<<endl;

            } else

        if (nameShort == string("JAS"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Jason_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Jason_Mic"<<endl;
                fout<<"Trait=TRAIT_Jason1"<<endl;
                fout<<"Trait=TRAIT_Jason2"<<endl;
                fout<<"Trait=TRAIT_Jason3"<<endl;
                fout<<"PlayerSelectPkgSuffix=_DLC"<<endl;

            } else

        if (nameShort == string("PRE"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Predator_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Predator_Mic"<<endl;
                fout<<"Trait=TRAIT_Predator1"<<endl;
                fout<<"Trait=TRAIT_Predator2"<<endl;
                fout<<"Trait=TRAIT_Predator3"<<endl;
                fout<<"PlayerSelectPkgSuffix=_DLC"<<endl;

            } else

        if (nameShort == string("TRE"))
            {
                fout<<"MaleTall"<<endl;
                fout<<"Dismemberment=DISM_MaleTall_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Tremor_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Tremor_Mic"<<endl;
                fout<<"Trait=TRAIT_Tremor1"<<endl;
                fout<<"Trait=TRAIT_Tremor2"<<endl;
                fout<<"Trait=TRAIT_Tremor3"<<endl;
                fout<<"PlayerSelectPkgSuffix=_DLC"<<endl;

            } else

        if (nameShort == string("TAN"))
            {
                fout<<"Female"<<endl;
                fout<<"Dismemberment=DISM_Female_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;
                fout<<"LadderRelief=UI_TWR_Reliefs_Tanya_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_Tanya_Mic"<<endl;
                fout<<"Trait=TRAIT_TanyaDLC1"<<endl;
                fout<<"Trait=TRAIT_TanyaDLC2"<<endl;
                fout<<"Trait=TRAIT_TanyaDLC3"<<endl;
                fout<<"PlayerSelectPkgSuffix=_DLC"<<endl;

            } else
            //For all Males
            {
                fout<<"Male"<<endl;
                fout<<"Dismemberment=DISM_Male_DLC"<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<endl;
                fout<<"Dismemberment=DISM_"<<CHARname<<"_DLC"<<endl;



                fout<<"LadderRelief=UI_TWR_Reliefs_";
                for (int i = 0; i <CHARname.length()-2 ; i++)
                    fout<<CHARname[i];
                fout<<"_St"<<endl;
                fout<<"LadderMic=UI_TWR_Reliefs_Wall_";
                for (int i = 0; i <CHARname.length()-2 ; i++)
                    fout<<CHARname[i];
                fout<<"_Mic"<<endl;
                for (int j = 0; j < 3; j++)
                {
                    fout<<"Trait=TRAIT_";
                    for (int i = 0; i <CHARname.length()-2 ; i++)
                        fout<<CHARname[i];
                    fout<<j+1<<endl;
                }

            }



        //After Comps
        delete [] nameShort;

    }

        fin.close();
        fout.close();
}
