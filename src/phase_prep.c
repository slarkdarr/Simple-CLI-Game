#include "phase_prep.h"
#include "stacklist.h"
#include "map.h"
#include "jam.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int preparation_phase() // buat jadi int return -1 kalo keluar prep phase tapi sekalian keluar dari game
{
    boolean prep_phase = true;

    int moneyNeeded = 0; 
    // Untuk display uang yang dibutuhkan, sekaligus dibandingkan dengan uang yang dimiliki saat memulai prep phase


    JAM batasTime = MakeJAM(12, 0, 1); // Batas time tiap prep phase 12 jam, karena memakai JLT maka dibuat 1 detik lebih lama agar dapat melakukan 12 jam worth of action
    JAM timeNeeded = MakeJAM(0, 0, 0); // Awalnya akan 0, untuk display waktu yang diperlukan

    Kata command;

    int nBuy; // jumlah barang yang dibeli
    Kata buyName; // nama barang

    Kata buildWahana; // setelah build, variable penyimpanan nama wahana yang akan di build

    int cont = 0; /////
    char* messageBuffer;
    int total_action = 0;// variable total aksi yang akan dilakukan
    Stack Actions;
    Stack TargetExecution;
    STACK_CreateEmpty(&Actions);
    STACK_CreateEmpty(&TargetExecution);
    DrawMap(_map, "Prep Phase\n");
    while(prep_phase)
    {
        printf("Perintah : ");
        ReadInput(&command); // Membaca input player menggunakan Mesin Kata
        switch(command.TabKata[0])
        {
            case 'w':
            case 'W':
                Move(&_map, 'W', &messageBuffer, &_fullMap);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'a':
            case 'A':
                Move(&_map, 'A', &messageBuffer, &_fullMap);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 's':
            case 'S':
                Move(&_map, 'S', &messageBuffer, &_fullMap);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'd':
            case 'D':
                Move(&_map, 'D', &messageBuffer, &_fullMap);
                DrawMap(_map, messageBuffer);
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
            case 'x':
                cont = -1;
                break;
            case 'b':
                if (IsKataSama(command, CreateKata("buy")))
                {
                    JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command));
                    // Berfungsi untuk check jika timeNeeded melebihi waktu pada prep phase
                    
                    if (JLT(JCheck, batasTime))
                    {
                        PrintBuyMaterials(); // Display Material yang dapat dibeli
                        printf("Kuantitas & Material : "); ReadCommand(&nBuy,&buyName); // Menggunakan Mesin Kata untuk membaca input player
                        // Input berupa kuantitas + jenis material yang akan dibeli
                        if (SearchForMaterial(_mlist, buyName)) // Mencari jika Jenis material yang diinput oleh pengguna terdapat dalam array of materials
                        // Jika terdapat mengembalikan true, jika tidak mengembalikan false
                        {
                            int price = nBuy * SearchForPrice(_mlist, buyName);
                            if ((nBuy > 0) && ((moneyNeeded + price) <= _money))
                            {
                                int indeks = SearchForIndexMaterial(buyName);
                                // Indeks dari Material yang diinput player (dalam Array of Materials)
                                Push(&Actions, command, indeks, nBuy, Player(_map), _fullMap); 
                                // Memasukkan action Buy beserta info-info yang diperlukan ke dalam Stack Actions
                                timeNeeded = JCheck; // timeNeeded ditambahkan (di set menjadi JCheck)
                                moneyNeeded += price; // Menambahkan moneyNeeded
                                DrawMap(_map, "Buy sukses\n");
                                PrintYourMaterials(); // Cek disini /////
                            }
                            else
                            {
                                if (nBuy <= 0) // Jika kuantitas yang diinput oleh player tidak valid, maka tidak dapat dibeli
                                {
                                    DrawMap(_map, "Kuantitas tidak valid\n");
                                }
                                else // Jika uang yang dimiliki tidak cukup
                                {
                                    DrawMap(_map, "Uang tidak mencukupi\n");
                                }
                            }
                        }
                        else // Jika input Jenis Material dari player salah
                        {
                            DrawMap(_map, "Material tidak terdapat pada katalog\n");
                        }
                    }
                    else // Jika waktu untuk Buy tidak cukup
                    {
                        DrawMap(_map, "Waktu tidak mencukupi\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                    // Print info player saat prep phase
                }
                else if (IsKataSama(command, CreateKata("build")))
                {
                    if (CheckNearGate(&_map) && CheckObject(&_map, 'O') && CheckObject(&_map, 'W') && CheckObject(&_map, 'w') && CheckObject(&_map, 'A'))
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command)); // Mengambil durasi dari action yang dilakukan dan ditambahkan dengan timeNeeded
                        // Haisl penjumlahan diassign pada JCheck, jika JCheck lebih dari batasTime maka aksi tidak dapat dilakukan
                        if (JLT(JCheck, batasTime)) // Mengecek jika waktu cukup untuk command build
                        {
                            PrintBuildableWahana(); // Print Wahana yang dapat dibuat
                            PrintYourMaterials(); // Print Bahan Bangunan yang dimiliki
                            printf("Wahana : "); ReadInput(&buildWahana); // Membaca input dari player berupa nama wahana yang akan dibuat
                            if (SearchForBuilding(buildWahana)) // Mencari jika nama Wahana terdapat pada Array of WahanTypes
                            {
                                int indeks = SearchForIndexBuilding(buildWahana); // Mencari indeks Wahana yang akan dibuat pada array of WahanaType
                                if (CheckMaterialCukup(indeks) && (moneyNeeded + WBuildPrice(_wType(indeks))) <= _money)
                                {
                                    MaterialQuantity(_mlist, 0) -= WWood(_wType(indeks)); // Mengonsumsi Wood
                                    MaterialQuantity(_mlist, 1) -= WStone(_wType(indeks)); // Mengonsumsi Wood
                                    MaterialQuantity(_mlist, 2) -= WIron(_wType(indeks)); // Mengonsumsi Wood

                                    TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) = 'w'; // w menandakan sedang dibuat, setelah execute akan menjadi W
                                    InfoElmtAtP(_map, Player(_map).X, Player(_map).Y) = indeks; // indeks array //indeks sementara pada map agar tidak bisa dijalani //CEK
                                    Push(&Actions, command, indeks, 1, Player(_map), _fullMap);
                                    Player(_map) = GetObjectP(&_map,'-'); // memindahkan player ke '-' terdekat
                                    DrawMap(_map, "");
                                    timeNeeded = JCheck;
                                    moneyNeeded += WBuildPrice(_wType(indeks));
                                }
                                else
                                {
                                    DrawMap(_map, "Bahan bangunan atau uang tidak cukup untuk build\n");
                                }
                            }
                            else
                            {
                                DrawMap(_map, "Wahana tidak terdapat dalam katalog\n");
                            }
                            
                        }
                        else
                        {
                            DrawMap(_map, "Waktu tidak mencukupi\n");
                        }
                    }
                    else
                    {
                        DrawMap(_map, "Tidak dapat membangun di depan gerbang atau di dalam Office/dekat office/dekat wahana/dekat Antrian\n");
                        // printf("Tidak dapat membangun di depan gerbang\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                }
                break;
            case 'u':
                if (IsKataSama(command, CreateKata("undo")))
                {
                    if (!STACK_IsEmpty(Actions))
                    {
                        Undo(&Actions, &timeNeeded, &moneyNeeded); // Menjalankan prosedur Undo
                        DrawMap(_map, "Undo sukses\n");
                    }
                    else
                    {
                        DrawMap(_map, "Tidak ada aksi untuk di Undo\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                }
                else if (IsKataSama(command, CreateKata("upgrade")))
                {
                    int cekobjek = GetObject(_map, 'W');
                    POINT cekpointobjek = GetObjectP(&_map, 'W'); // untuk mengganti W menjadi w sebagai tanda sedang upgrade
                    if (cekobjek != -10)
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command));
                        if (JLT(JCheck, batasTime)) // Mengecek jika waktu cukup untuk command upgrade
                        {
                            if (!WAHANA_TREE_IsOneElmt((_wahana(cekobjek)).current))
                            // Mengecek jika Wahana masih bisa di upgrade, jika merupakan OneElmt (tidak memiliki left dan right)
                            // Maka tidak dapat diupgrade lagi
                            {
                                if (WAHANA_TREE_IsBiner((_wahana(cekobjek)).current))
                                // Mengecek jika Wahana memiliki Left dan Right, agar tidak membandingkan Kata dengan WNama(Nil)
                                {
                                    Kata untukUpgrade;
                                    WAHANA_PrintCommandUpgrade((_wahana(cekobjek)).current); // Menampilkan opsi upgrade yang tersedia
                                    printf("Pilihan Upgrade : ");ReadInput(&untukUpgrade); // Input
                                    if (IsKataSama(untukUpgrade, WNama(Left((_wahana(cekobjek)).current)))) // CEK
                                    {
                                        if (CheckUpgradeCukup(Left((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Left((_wahana(cekobjek)).current)) <= _money))
                                        // Mengecek jika uang cukup
                                        // Mengecek jika cukup untuk upgrade dan langsung mengurangkan bahan bangunan
                                        {
                                            MaterialQuantity(_mlist, 0) -= WWood(Left((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 1) -= WStone(Left((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 2) -= WIron(Left((_wahana(cekobjek)).current));
                                            Push(&Actions, command, cekobjek, 1, cekpointobjek, _fullMap);
                                            // 1 berarti left
                                            moneyNeeded += WBuildPrice(Left((_wahana(cekobjek)).current));
                                            timeNeeded = JCheck;
                                            for (int i = 0; i < (_wahana(cekobjek)).size; i++)
                                            {
                                                POINT PP = (_wahana(cekobjek)).exPosition[i];
                                                TypeElmtAtP(_map, PP.X, PP.Y) = 'w';
                                            }
                                            // TypeElmtAtP(_map, cekpointobjek.X, cekpointobjek.Y) = 'w';
                                            DrawMap(_map, "Upgrade sukses\n");
                                        }
                                        else
                                        {
                                            DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                        }
                                    }
                                    else if (IsKataSama(untukUpgrade, WNama(Right((_wahana(cekobjek)).current))))
                                    {
                                        if (CheckUpgradeCukup(Right((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Right((_wahana(cekobjek)).current)) <= _money))
                                        {
                                            MaterialQuantity(_mlist, 0) -= WWood(Right((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 1) -= WStone(Right((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 2) -= WIron(Right((_wahana(cekobjek)).current));
                                            Push(&Actions, command, cekobjek, 0, cekpointobjek, _fullMap);
                                            // 0 berarti right
                                            moneyNeeded += WBuildPrice(Right((_wahana(cekobjek)).current));
                                            timeNeeded = JCheck;
                                            for (int i = 0; i < (_wahana(cekobjek)).size; i++)
                                            {
                                                POINT PP = (_wahana(cekobjek)).exPosition[i];
                                                TypeElmtAtP(_map, PP.X, PP.Y) = 'w';
                                            }
                                            // TypeElmtAtP(_map, cekpointobjek.X, cekpointobjek.Y) = 'w';
                                            DrawMap(_map, "Upgrade sukses\n");
                                        }
                                        else
                                        {
                                            DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                        }
                                    }
                                    else
                                    {
                                        DrawMap(_map, "Pilihan upgrade tidak terdapat dalam katalog\n");
                                    }
                                }
                                else if (WAHANA_TREE_IsUnerLeft((_wahana(cekobjek)).current))
                                // Mengecek jika HANYA terdapat left pada tree upgrade wahana
                                {
                                    Kata untukUpgrade;
                                    WAHANA_PrintCommandUpgradeLeft((_wahana(cekobjek)).current); // Menampilkan opsi upgrade yang tersedia
                                    printf("Pilihan Upgrade : ");ReadInput(&untukUpgrade); // Input
                                    if (IsKataSama(untukUpgrade, WNama(Left((_wahana(cekobjek)).current))))
                                    {
                                        if (CheckUpgradeCukup(Left((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Left((_wahana(cekobjek)).current)) <= _money))
                                        //cek jika uang cukup
                                        //cek jika cukup untuk upgrade dan langsung mengurangkan bahan bangunan
                                        {
                                            MaterialQuantity(_mlist, 0) -= WWood(Left((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 1) -= WStone(Left((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 2) -= WIron(Left((_wahana(cekobjek)).current));
                                            Push(&Actions, command, cekobjek, 1, cekpointobjek, _fullMap);
                                            // 1 berarti left
                                            moneyNeeded += WBuildPrice(Left((_wahana(cekobjek)).current));
                                            timeNeeded = JCheck;
                                            for (int i = 0; i < (_wahana(cekobjek)).size; i++)
                                            {
                                                POINT PP = (_wahana(cekobjek)).exPosition[i];
                                                TypeElmtAtP(_map, PP.X, PP.Y) = 'w';
                                            }
                                            // TypeElmtAtP(_map, cekpointobjek.X, cekpointobjek.Y) = 'w';
                                            DrawMap(_map, "Upgrade sukses\n");
                                        }
                                        else
                                        {
                                            DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                        }
                                    }
                                    else
                                    {
                                        DrawMap(_map, "Pilihan upgrade tidak terdapat dalam katalog\n");
                                    }
                                }
                                else if (WAHANA_TREE_IsUnerRight((_wahana(cekobjek)).current))
                                // Mengecek jika HANYA terdapat right pada upgrade tree wahana
                                {
                                    Kata untukUpgrade;
                                    WAHANA_PrintCommandUpgradeRight((_wahana(cekobjek)).current); // Menampilkan opsi upgrade yang tersedia
                                    printf("Pilihan Upgrade : ");ReadInput(&untukUpgrade); // Input
                                    if (IsKataSama(untukUpgrade, WNama(Right((_wahana(cekobjek)).current))))
                                    {
                                        if (CheckUpgradeCukup(Right((_wahana(cekobjek)).current)) && (moneyNeeded + WBuildPrice(Right((_wahana(cekobjek)).current)) <= _money))
                                        {
                                            MaterialQuantity(_mlist, 0) -= WWood(Right((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 1) -= WStone(Right((_wahana(cekobjek)).current));
                                            MaterialQuantity(_mlist, 2) -= WIron(Right((_wahana(cekobjek)).current));
                                            Push(&Actions, command, cekobjek, 0, cekpointobjek, _fullMap);
                                            // 0 berarti right
                                            moneyNeeded += WBuildPrice(Right((_wahana(cekobjek)).current));
                                            timeNeeded = JCheck;
                                            for (int i = 0; i < (_wahana(cekobjek)).size; i++)
                                            {
                                                POINT PP = (_wahana(cekobjek)).exPosition[i];
                                                TypeElmtAtP(_map, PP.X, PP.Y) = 'w';
                                            }
                                            // TypeElmtAtP(_map, cekpointobjek.X, cekpointobjek.Y) = 'w';
                                            DrawMap(_map, "Upgrade sukses\n");
                                        }
                                        else
                                        {
                                            DrawMap(_map, "Bahan bangunan atau uang tidak cukup\n");
                                        }
                                    }
                                    else
                                    {
                                        DrawMap(_map, "Pilihan upgrade tidak terdapat dalam katalog\n");
                                    }
                                }
                            }
                            else
                            {
                                DrawMap(_map, "Wahana tidak dapat diupgrade lagi\n");
                            }
                        }
                        else
                        {
                            DrawMap(_map, "Waktu tidak cukup untuk upgrade\n");
                        } 
                    }
                    else
                    {
                        DrawMap(_map, "Tidak ada Wahana untuk di Upgrade\nTunggu satu hari semenjak build untuk mengupgrade Wahana\nTidak bisa mengupgrade wahana yang sedang dalam proses upgrade\n");
                    }
                    info_prep(Actions, timeNeeded, moneyNeeded);
                    // Display info player
                }
                break;
            case 'e':
                if (IsKataSama(command, CreateKata("execute")))
                {
                    toTarget(&Actions, &TargetExecution);
                    // Memindahkan Stack dari Actions ke Target Execution untuk dieksekusi
                    // Dilakukan agar action yang pertama kali dilakukan dieksekusi pertama kali
                    Execute(&TargetExecution, &_money);
                    // Melakukan eksekusi sesuai dengan tipe action pada Stack
                    _money -= moneyNeeded; 
                    // Mengurangkan money yang dimiliki sesuai dengan money yang diperlukan untuk melakukan semua action
                    prep_phase = false;
                    // Set prep_phase menjadi false agar keluar dari while loop, melanjutkan ke main phase
                    SetOpen(&_time);
                    // Mengganti variable global JAM _time menjadi jam untuk buka Wahana
                    TulisJAM(_time); printf("\n");
                    STACK_CreateEmpty(&Actions);
                    STACK_CreateEmpty(&TargetExecution);
                    DrawMap(_map, "Pindah ke main phase\n");
                    // Set jam ke jam buka, pindah ke main phase
                } else if (IsKataSama(command, CreateKata("extend")))
                {   
                    /*NAMBAH UKURAN*/
                    if (CheckNearGate(&_map) && CheckObject(&_map, 'O') && CheckObject(&_map, 'w') && CheckObject(&_map, 'A'))
                    {
                        JAM JCheck = NextNDetik(timeNeeded, GetDuration(_actions, command)); // Mengambil durasi dari action yang dilakukan dan ditambahkan dengan timeNeeded
                        // Haisl penjumlahan diassign pada JCheck, jika JCheck lebih dari batasTime maka aksi tidak dapat dilakukan
                        if (JLT(JCheck, batasTime)) // Mengecek jika waktu cukup untuk command build
                        {
                            int idWahana = GetObject(_map, 'W');
                            PrintYourMaterials(); // Print Bahan Bangunan yang dimiliki
                            
                            if (idWahana != -10) // Mencari jika nama Wahana terdapat pada Array of WahanTypes
                            {
                                int indeks = idWahana; // Mencari indeks Wahana yang akan dibuat pada array of WahanaType
                                printf("Wahana : "); PrintKata(WNama(_wahana(idWahana).current)); ln;
                                if (CheckMaterialCukup(indeks) && (moneyNeeded + WBuildPrice(_wType(indeks))) <= _money)
                                {
                                    MaterialQuantity(_mlist, 0) -= WWood(_wType(indeks)); // Mengonsumsi Wood
                                    MaterialQuantity(_mlist, 1) -= WStone(_wType(indeks)); // Mengonsumsi Wood                
                                    MaterialQuantity(_mlist, 2) -= WIron(_wType(indeks)); // Mengonsumsi Wood

                                    TypeElmtAtP(_map, Player(_map).X, Player(_map).Y) = 'w'; // w menandakan sedang dibuat, setelah execute akan menjadi W
                                    InfoElmtAtP(_map, Player(_map).X, Player(_map).Y) = indeks; // indeks array //indeks sementara pada map agar tidak bisa dijalani
                                    Push(&Actions, command, indeks, 1, Player(_map), _fullMap);
                                    Player(_map) = GetObjectP(&_map,'-'); // memindahkan player ke '-' terdekat
                                    DrawMap(_map, "");
                                    timeNeeded = JCheck;
                                    moneyNeeded += WBuildPrice(_wType(indeks));
                                    
                                }
                                else
                                {
                                    DrawMap(_map, "Bahan bangunan atau uang tidak cukup untuk build\n");
                                }
                            }
                            else
                            {
                                DrawMap(_map, "Tidak ada wahana di dekat anda\n");
                            }
                            
                        }
                        else
                        {
                            DrawMap(_map, "Waktu tidak mencukupi\n");
                        }
                    }
                    else
                    {
                        DrawMap(_map, "Tidak dapat membangun di depan gerbang atau di dalam Office/dekat office/dekat wahana/dekat Antrian\n");
                        // printf("Tidak dapat membangun di depan gerbang\n");
                    }
                    TulisIsiTab(_actions);
                    info_prep(Actions, timeNeeded, moneyNeeded);
                }
                break;
                break;
            case 'm':
                if (IsKataSama(command, CreateKata("main")))
                {
                    // Jika main maka tidak melakukan aksi pada Stack
                    // Atau meng-undo semua action pada Stack dan langsung melanjutkan ke main phase
                    while (!STACK_IsEmpty(Actions)) // Selama Stack Actions tidak empty dilakukan Undo pada semua isi nya
                    {
                        Undo(&Actions, &timeNeeded, &moneyNeeded);
                    }
                    prep_phase = false;
                    // Set prep_phase menjadi false agar keluar dari while loop, melanjutkan ke main phase
                    SetOpen(&_time);
                    // Mengganti variable global JAM _time menjadi jam saatnya untuk buka Wahana
                    STACK_CreateEmpty(&Actions);
                    STACK_CreateEmpty(&TargetExecution);
                    DrawMap(_map, "Pindah ke main phase\n");
                    // Set jam ke jam buka, pindah ke main phase
                }
                break;
            default :
                DrawMap(_map, "Perintah tidak diketahui\n");
                info_prep(Actions, timeNeeded, moneyNeeded);
                break;
        }
    }
    return 0;
}

//ini command yang dijalanin kalo command build, tambahin build ke stack
void Build(MAP *M, POINT P, int i, gAddress_V mapStack) //indeks pada array wahana
{
    POINT Point = Player(_map);
    WAHANA_CreateInstance(P, i, mapStack);
    _map = VertexMap(_fullMap);
    Player(_map) = Point;
    // Memasukkan Wahana pada Array yang berisi wahana yang terdapat dalam map
    // Mengganti TypeElmtAtP menjadi 'W' dengan Info menunjuk ke array pada wahana
}


void Extend(gAddress_V M, POINT P, int i)
{
    POINT prePlayer = Player(_map);
    WAHANA_ExtendInstance(M, P, i);
    _map = VertexMap(_fullMap);
    Player(_map) = prePlayer;
}

void Upgrade(POINT P, int specCommand_, int infoCommand_, gAddress_V mapStack_)
// Mengakses array of Wahana Instance, upgrade wahana instance
// specCommand_ merupakan indeks array of Wahana Instance, infoCommand_ menentukan upgrade ke left atau right
// infoCommand_ == 1 berarti Left, infoCommand_ == 0 berarti Right
{
    POINT Point = Player(_map);
    for (int i = 0; i < (_wahana(specCommand_)).size; i++)
    {
        POINT PP = (_wahana(specCommand_)).exPosition[i];
        TypeElmtAtP(VertexMap(mapStack_), PP.X, PP.Y) = 'W';
    }
     // Penanda upgrade selesai, TypeElement menjadi W lagi
    if (infoCommand_) // Jika infoCommand_ == 1 atau true maka Left
    {
        (_wahana(specCommand_)).current = Left(_wahana(specCommand_).current); // Mengganti current wahana Type pada Array of Wahana
        Test(17);
        AddToUpgradeHistory(&_wahana(specCommand_).upgrades, true); // Menambahkan left dari upgrade terakhir ke history
        // (_wahana(specCommand_)).upgradeHistory[(_wahana(specCommand_)).upgradeHistoryNEff] = true; // Insersi pada NEff array boolean
        // (_wahana(specCommand_)).upgradeHistoryNEff += 1; // Menambah NEff dari history upgrade wahana
    }
    else // Jika infoCommand_ == 0 atau false maka Right
    {
        Test(18);
        (_wahana(specCommand_)).current = Right(_wahana(specCommand_).current); // Mengganti current wahana Type pada Array of Wahana
        Test(19);
        AddToUpgradeHistory(&_wahana(specCommand_).upgrades, false); // Menambahkan left dari upgrade terakhir ke history
        // (_wahana(specCommand_)).upgradeHistory[(_wahana(specCommand_)).upgradeHistoryNEff] = false; // Insersi pada NEff array boolean
        // (_wahana(specCommand_)).upgradeHistoryNEff += 1; // Menambah NEff dari history upgrade wahana
    }
    _map = VertexMap(_fullMap);
    Player(_map) = Point;
}

void Buy(TabMaterial *TabMat, int Jumlah, int Index)
{
    MaterialQuantity(*TabMat, Index) += Jumlah; // Menambahkan jumlah pada Array of Materials dari gameInstance
    // menambahkan kuantitas pada TabMat
}

// sebelum execut pindah stack ke stack target dan lakukan dari aksi awal
void Execute(Stack *S, int *globalCurrency)
{
    Kata command_;
    int specCommand_;
    int infoCommand_;
    POINT pointPlayer_;
    gAddress_V mapStack_;

    // Kata pembanding
    Kata KataBuild = CreateKata("build");
    Kata KataUpgrade = CreateKata("upgrade");
    Kata KataBuy = CreateKata("buy");
    Kata KataExtend = CreateKata("extend");

    while (!STACK_IsEmpty(*S))
    {
        Pop(S, &command_, &specCommand_, &infoCommand_, &pointPlayer_, &mapStack_);
        if (IsKataSama(command_, KataBuild))
        {
            Build(&_map, pointPlayer_, specCommand_, mapStack_); // Melaksanakan Build
        }
        else if (IsKataSama(command_, KataUpgrade))
        {
            Upgrade(pointPlayer_, specCommand_, infoCommand_, mapStack_); // Melaksanakan Upgrade
        }
        else if (IsKataSama(command_, KataBuy))
        {
            Buy(&_mlist, infoCommand_, specCommand_); // Menambah kuantitas bahan bangunan yang dimiliki
        } else if (IsKataSama(command_, KataExtend))
        {
            Extend(mapStack_, pointPlayer_, specCommand_);
        }
    }
}

void toTarget(Stack *S, Stack *Target)
// Stack Target di Create Empty terlebih dahulu
// Lalu baru dieksekusi
{
    Kata command_;
    int specCommand_;
    int infoCommand_;
    POINT pointPlayer_;
    gAddress_V mapStack_;
    while (!STACK_IsEmpty(*S))
    {
        Pop(S, &command_, &specCommand_, &infoCommand_, &pointPlayer_, &mapStack_);
        Push(Target, command_, specCommand_, infoCommand_, pointPlayer_, mapStack_);
    }
}

void Undo (Stack *S, JAM *timeNeeded, int *moneyNeeded) // untuk fungsi user undo 
// MoneyNeeded dikurangkan, Time needed dikurangkan
// Pengurangan sesuai tiap command yang di Undo
{
    Kata command__; // Menyimpan tipe action yang di Undo
    int specCommand__; // Menyimpan spesifikasi dari action yang dilakukan, memiliki arti yang berbeda untuk action yang berbeda
    int infoCommand__; // Info dari command yang dilakukan
    POINT pointPlayer__; // Point player / Point bangunan
    gAddress_V mapStack__; // Lokasi Map saat melakukan command tersebut
    POINT Point = Player(_map);
    addressStack P = Top(*S);
    if (P == STACK_Nil)
    {
        printf("Tidak ada aksi untuk di undo\n");
        // Jika stack kosong, maka keluar pesan error
    }
    else
    {
        Pop(S, &command__, &specCommand__, &infoCommand__, &pointPlayer__, &mapStack__); 
        // Melakukan pop dari Stack meng-assign tiap elemen pada hasil pop ke variable di atas
        if (IsKataSama(command__, CreateKata("build")))
        {
            int x = pointPlayer__.X;
            int y = pointPlayer__.Y;
            InfoElmtAtP(VertexMap(mapStack__), x, y) = -1; // Mengembalikan info elemen agar dapat dilangkahi lagi oleh player
            TypeElmtAtP(VertexMap(mapStack__), x, y) = '-'; // Mengembalikan ke karakter '-'
            Buy(&_mlist, WWood(_wType(specCommand__)), 0); // refund wood
            Buy(&_mlist, WStone(_wType(specCommand__)), 1); // refund stone
            Buy(&_mlist, WIron(_wType(specCommand__)), 2); // refund iron
            *moneyNeeded -= WBuildPrice(_wType(specCommand__)); // refund uang
            // refund bahan bangunan dan uang
        }
        else if (IsKataSama(command__, CreateKata("upgrade")))
        {
            if (infoCommand__) // if infoCommand__ == 1 or true maka Left dari current Wahana
            {
                Buy(&_mlist, WWood(Left((_wahana(specCommand__)).current)), 0); // refund wood
                Buy(&_mlist, WStone(Left((_wahana(specCommand__)).current)), 1); // refund stone
                Buy(&_mlist, WIron(Left((_wahana(specCommand__)).current)), 2); // refund iron
                *moneyNeeded -= WBuildPrice(Left((_wahana(specCommand__)).current)); // refund money
                // refund bahan bangunan dan uang
            }
            else // infoCommand__ == 0 or false, maka Right dari current Wahana
            {
                Buy(&_mlist, WWood(Right((_wahana(specCommand__)).current)), 0); // refund wood
                Buy(&_mlist, WStone(Right((_wahana(specCommand__)).current)), 1); // refund stone
                Buy(&_mlist, WIron(Right((_wahana(specCommand__)).current)), 2); // refund iron
                *moneyNeeded -= WBuildPrice(Right((_wahana(specCommand__)).current)); // refund money
                // refund bahan bangunan dan uang
            }
            for (int i = 0; i < (_wahana(specCommand__)).size; i++)
            {
                POINT PP = (_wahana(specCommand__)).exPosition[i];
                TypeElmtAtP(VertexMap(mapStack__), PP.X, PP.Y) = 'W';
            }
            // Membuat karater pada posisi.X, posisi.Y menjadi karakter 'W' atau W kapital, menandakan build sudah selesai
        }
        else if (IsKataSama(command__, CreateKata("buy")))
        {
            *moneyNeeded -= infoCommand__ * MaterialPrice(_mlist, specCommand__);
            // Mengurangkan moneyNeeded (menambahkan uang yang dapat digunakan)
        } else if (IsKataSama(command__, CreateKata("build")))
        {
            int x = pointPlayer__.X;
            int y = pointPlayer__.Y;
            InfoElmtAtP(VertexMap(mapStack__), x, y) = -1; // Mengembalikan info elemen agar dapat dilangkahi lagi oleh player
            TypeElmtAtP(VertexMap(mapStack__), x, y) = '-'; // Mengembalikan ke karakter '-'
            Buy(&_mlist, WWood(_wType(specCommand__)), 0); // refund wood
            Buy(&_mlist, WStone(_wType(specCommand__)), 1); // refund stone
            Buy(&_mlist, WIron(_wType(specCommand__)), 2); // refund iron
            *moneyNeeded -= WBuildPrice(_wType(specCommand__)); // refund uang
            // refund bahan bangunan dan uang
        } else if (IsKataSama(command__, CreateKata("extend")))
        {
            int x = pointPlayer__.X;
            int y = pointPlayer__.Y;
            InfoElmtAtP(VertexMap(mapStack__), x, y) = -1; // Mengembalikan info elemen agar dapat dilangkahi lagi oleh player
            TypeElmtAtP(VertexMap(mapStack__), x, y) = '-'; // Mengembalikan ke karakter '-'
            Buy(&_mlist, WWood(_wType(specCommand__)), 0); // refund wood
            Buy(&_mlist, WStone(_wType(specCommand__)), 1); // refund stone
            Buy(&_mlist, WIron(_wType(specCommand__)), 2); // refund iron
            *moneyNeeded -= WBuildPrice(_wType(specCommand__)); // refund uang
            // refund bahan bangunan dan uang
        }
        long waktu = JAMToDetik(*timeNeeded); // Mengkonversikan *timeNeeded menjadi long terlebih dahulu
        waktu -= GetDuration(_actions, command__); // Mengambil durasi dari action yang dilakukan dari array of actions, lalu waktu dikurangkan sebanyak hasil
        *timeNeeded = DetikToJAM(waktu); // Mengurangkan timeNeeded sesuai dengan tipe action yang dilakukan
    }
    _map = VertexMap(_fullMap);
    Player(_map) = Point;
}

boolean SearchForBuilding(Kata Building)
// Untuk memasukkan perintah build ke stack, cari dulu bangunannya ada atau tidak
// Input tipe Kata, mengembalikan boolean true jika ditemukan, false, jika tidak
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(WNama(_wType(i)), Building))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return found;
}

int SearchForIndexBuilding(Kata Building)
// Return Indeks Building pada array setelah dicek true atau tidak (SearchForBuilding)
// Input berupa Kata yang sebelumnya sudah dicek ada atau tidak dalam array of wahana type yang dapat dibuat
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(WNama(_wType(i)), Building))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return i;
}

boolean CheckNearGate(MAP *M)
// Fungsi untuk cek bisa build, agar tidak build di sebelah gate
{
    if (TypeElmtAtP(*M, (Player(*M).X) - 1, Player(*M).Y) == '<')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), Player(*M).Y) == '>')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y + 1)) == 'V')
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y - 1)) == '^')
    {
        return false;
    }
    else
    {
        return true;
    }  
}

void info_prep(Stack Action, JAM timeNeeded, int moneyNeeded)
// Prosedur untuk display informasi player saat preparation phase
{
    Kata KName = CreateKata(_name); 

    printf("Nama                            :   "); PrintKata(KName); printf("\n"); 
    printf("Money                           :   %d\n", _money); 
    printf("Current Time                    :   21.00\n"); 
    printf("Opening Time                    :   09.00\n");
    printf("Time Remaining                  :   12 jam\n");
    printf("Total aksi yang akan dilakukan  :   %d\n", STACK_NbElmt(Action));
    printf("Total waktu yang dibutuhkan     :   "); TulisJAM(timeNeeded); printf("\n");
    printf("Total uang yang dibutuhkan      :   %d", moneyNeeded); printf("\n");
}

int SearchForIndexMaterial(Kata Material)
// Mencari index material dengan input Kata Material
{
    int i = 0;
    boolean found = false;
    while (!found && i < _wTCount)
    {
        if (IsKataSama(Material, MaterialName(_mlist, i))) // Mengecek jika kata sama
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return i;
}

void PrintNamaWahana()
// Tidak digunakan
{
    printf("List nama wahana:\n");
    for (int i=0; i<_wTCount;i++)
    {
        printf("- "); PrintKata(WNama(_wType(i))); printf("\n");
    }
}

void PrintUpgradeWahana(int i) //i adalah indeks base build
// Digunakan untuk display list upgrade wahana
{
    Kata UpgradeOne = WNama(Left(_wType(i))); //tanya govin bener apa engga
    Kata UpgradeTwo = WNama(Right(_wType(i)));
    printf("Upgrade menjadi : \n");
    printf("- "); PrintKata(UpgradeOne);
    printf("- "); PrintKata(UpgradeTwo);
    printf("  Pilihan: ");
}

void PrintBuildableWahana()
// Display Wahana yang dapat di build
{
    printf("List Wahana yang dapat dibuat: \n");
    int i;
    for (int i = 0; i < _wTCount; i++)
    {
        printf("    -  "); PrintKata(WNama(_wType(i))); printf("\n");
        printf("       Deskripsi : "); PrintKata(WDeskripsi(_wType(i))); printf("\n");
        printf("       Bahan     :  Wood : %d  Stone : %d  Iron : %d\n", WWood(_wType(i)), WStone(_wType(i)), WIron(_wType(i)));
        printf("       Price     : %d\n", WBuildPrice(_wType(i)));
    }
}

void PrintYourMaterials()
// Print material yang dimiliki (kuantitas dan jenis material)
{
    printf("Your Materials: \n");
    printf("Wood : %d\n", MaterialQuantity(_mlist, 0));
    printf("Stone: %d\n", MaterialQuantity(_mlist, 1));
    printf("Iron : %d\n", MaterialQuantity(_mlist, 2));
    // Tidak menggunakan for loop agar indentasi Colon (:) tepat dan enak dilihat
}

boolean CheckObject(MAP *M, char C)
// Mencari jika object dengan TypeElmt char C ada di dekat atau pada player
// Mengirimkan false jika terdapat objek dengan TypeElmt char C di sekitar player (atau pada player)
// Mengirimkan true jika tidak terdapat
{
    if (TypeElmtAtP(*M, (Player(*M).X) - 1, Player(*M).Y) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), Player(*M).Y) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X - 1), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X - 1), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), (Player(*M).Y - 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X + 1), (Player(*M).Y + 1)) == C)
    {
        return false;
    }
    else if (TypeElmtAtP(*M, (Player(*M).X), (Player(*M).Y)) == C)
    {
        return false;
    }
    else
    {
        return true;
    }  
}

boolean CheckMaterialCukup(int i)
// Mengecek jika material cukup dan langsung ke proses build Wahana (langsung mengurangi bahan bangunan yang dimiliki)
{
    if (MaterialQuantity(_mlist, 0) >= WWood(_wType(i)) && MaterialQuantity(_mlist, 1) >= WStone(_wType(i)) && MaterialQuantity(_mlist, 2) >= WIron(_wType(i)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PrintBuyMaterials()
// Display Material yang dapat dibeli
{
    printf("List Material : \n");
    for (int i = 0; i < 3; i++)
    {
        printf("    -  "); PrintKata(MaterialName(_mlist, i)); printf("  Harga: %d\n", MaterialPrice(_mlist, i));
    }
    // Perlu pake for loop apa gausah ? tentuin nanti
}

boolean CheckUpgradeCukup(tAddress W)
// Mengecek jika upgrade cukup untuk dilaksanakan
{
    if (MaterialQuantity(_mlist, 0) >= WWood(W) && MaterialQuantity(_mlist, 1) >= WStone(W) && MaterialQuantity(_mlist, 2) >= WIron(W))
    {
        return true;
    }
    else
    {
        return false;
    }
}
///// This is for extend
// for (int i = 0; i < (_wahana(specCommand_)).size; i++)
//     {
//         POINT PP = (_wahana(specCommand_)).exPosition[i];
//         TypeElmtAtP(VertexMap(mapStack_), PP.X, PP.Y) = 'W';
//     }