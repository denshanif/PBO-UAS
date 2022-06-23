#include <iostream>
#include <conio.h>
#include <vector>
#include <cmath>

using namespace std;

// Seluruh class
class Tampilan;
class User;
class UserBaru;
class Staff;
class Pelanggan;
class Menu;
class Tagihan;

// Buat head untuk class Menu dan class Pelanggan
Menu* head;
Pelanggan* headPelanggan;

// Variabel untuk menampung banyak data dan order
int data = 0, order = 0;

class Tampilan {
  public:
    void awal();
    void tipePengguna();
    void loginStaff();
    void welcome();
    void menuStaff();
    void menuPelanggan();
};

class User {
  private:
    string user;
    string pass;
  public:
    User(){
      this->user = " ";
      this->pass = " ";
    }
    User(string user, string pass){
      this->user = user;
      this->pass = pass;
    }
    string getuser(){
      return user;
    }
    string getpass(){
      return pass;
    }
};

class UserBaru : public User {
  private:
    vector<User> staff;
  public:
    UserBaru(){
      this->staff.push_back(User("admin","admin"));
    }
    bool cek(string user, string pass){
      for(int i=0; i<staff.size();i++){
        if(staff[i].getuser() == user && staff[i].getpass() == pass){
          return true;
        }
      }
      return false;
    }
    User getuser(string user, string pass){
      for(int i=0; i<staff.size();i++){
        if(staff[i].getuser() == user && staff[i].getpass() == pass){
          return staff[i];
        }
      }
      return User();
    }
};

class Menu {
  public:
    int idItem;
    string namaItem;
    int hargaItem;
    Menu *next;

    Menu() {
      next = NULL;
    }

    Menu(int id, string nama, int harga)
    {
      this->idItem = id;
      this->namaItem = nama;
      this->hargaItem = harga;
      this->next = NULL;
    }

    void tampilMenu()
    {
      data = 0;
      Menu *temp = head;
      while (temp != NULL)
      {
          cout << "ID Item: " << temp->idItem << endl;
          cout << "Nama Item: " << temp->namaItem << endl;
          cout << "Harga Item: " << temp->hargaItem << endl;
          temp = temp->next;
      }
      data++;
      cout << "Jumlah Item Pada Menu: " << data << endl;
    }
};

Menu menu;

class Pelanggan {
  public:
    string namaPelanggan;
    int nomorMeja;
    int idPemesanan;
    Pelanggan *next;

    Pelanggan()
    {
      headPelanggan = NULL;
      next = NULL;
    }

    Pelanggan(string nama, int noMeja, int idPemesanan)
    {
      this->namaPelanggan = nama;
      this->nomorMeja = noMeja;
      this->idPemesanan = idPemesanan;
      this->next = NULL;
    }

    bool validasiMeja(int);
    void pemesanan();
    int bill(int);
    void bayar(int);
    void menuHariIni()
    {
      system("cls");
      cout << "==============MENU HARI INI==============\n\n" << endl;
      if (head != NULL)
      {
        menu.tampilMenu();
      }
      else
        cout << "MENU KOSONG!\n\n" << endl;
    }
};

class Staff
{
  private:
    int validasi;
  public:
    void lihatMenu()
    {
      system("cls");
      cout << "=================SELURUH MENU==============\n\n" << endl;
      if (head != NULL)
      {
        menu.tampilMenu();
      }
      else
        cout << "MENU KOSONG!\n\n" << endl;
    }

    void tambahMenu()
    {
      int id, flag;
      flag = 0;
      string nama;
      int harga;

      ulang:
      cout << "=================TAMBAH MENU==============\n\n" << endl;
      cout << "Masukkan Id Item: ";
      cin >> id;
      Menu *temp;
      temp = head;
      while (temp != NULL)
      {
        if (temp->idItem == id)
        {
          cout << "Item dengan id " << id << " telah ada, tambahkan id lain!\n";
          flag = 1;
          break;
        }
        temp = temp->next;
      }
      if (flag == 1)
        tambahMenu();
      else {
        cout << "Masukkan Nama Item: ";
        cin >> ws;
        getline(cin, nama);
        cout << "Masukkan Harga Item: Rp.";
        cin >> harga;

        Menu* newNode = new Menu(id, nama, harga);

        if (head == NULL)
        {
          data++;
          head = newNode;
        }
        else
        {
          Menu *temp = head;
          while (temp->next != NULL)
          {
            temp = temp->next;
          }

          temp->next = newNode;
          data++;
        }
      }
    }

    void hapusMenu()
    {
      int hapus;
      validasi = 0;

      lihatMenu();

      if (head != NULL)
      {
        cout << "\n\n=================HAPUS MENU================\n\n" << endl;
        cout << "Masukkan Id Item Yang Ingin Dihapus: ";
        cin >> hapus;

        Menu *temp1 = head, *temp2 = NULL;

        validasi++;
        while (temp1 != NULL)
        {
          if (temp1->idItem == hapus)
          {
            break;
          }
          temp2 = temp1;
          temp1 = temp1->next;
          validasi++;
        }

        if (data < validasi)
        {
          cout << "Item yang ingin dihapus tidak ditemukan!";
          hapusMenu();
        }
        else if (validasi == 1)
        {
          head = head->next;
          delete temp1;
          data--;
        }
        else
        {
          temp2->next = temp1->next;

          delete temp1;
          data--;
        }
      }
    }

    void ubahMenu()
    {
      int ubah;
      validasi = 0;

      lihatMenu();

      if (head != NULL)
      {
        cout << "\n\n=================UBAH MENU================\n\n" << endl;
        cout << "Masukkan Id Item Yang Ingin Diubah: ";
        cin >> ubah;

        Menu *temp = head;

        validasi++;
        while (temp != NULL)
        {
          if (temp->idItem == ubah)
          {
            break;
          }
          temp = temp->next;
          validasi++;
        }

        if (data < validasi)
        {
          cout << "Item yang ingin diubah tidak ditemukan!";
          ubahMenu();
        }
        else
        {
          cout << "Masukkan nama item: ";
          cin >> ws;
          getline(cin, temp->namaItem);
          cout << "Masukkan harga item: Rp.";
          cin >> temp->hargaItem;
        }
      }
    }
};

class Tagihan
{
public:
    int t;
    Tagihan(int tagihan = 0)
    {
        this->t = tagihan;
    }

    Tagihan operator+(Tagihan const &obj)
    {
        Tagihan jumlah;
        jumlah.t = t + obj.t;
        return jumlah;
    }
};

Staff staff;

void Tampilan::menuStaff() {
  system("Color 0A");
  char pilihan;
  menu:
    system("cls");
    cout << "HALAMAN STAFF...\n";
    cout << "1. Tambah item makanan ke menu\n";
    cout << "2. Tampilkan semua item pada menu\n";
    cout << "3. Hapus item pada menu\n";
    cout << "4. Ubah item pada menu\n";
    cout << "5. Kembali ke menu sebelumnya\n";
    cout << "Masukkan pilihan anda: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case '1':
      staff.tambahMenu();
      cout << "Menu berhasil ditambahkan\n";
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      goto menu;
    case '2':
      staff.lihatMenu();
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      goto menu;
    case '3':
      staff.hapusMenu();
      cout << "Item berhasil dihapus\n\n";
      staff.lihatMenu();
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      goto menu;
    case '4':
      staff.ubahMenu();
      cout << "Item berhasil diubah\n\n";
      staff.lihatMenu();
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      goto menu;
    case '5':
      system("cls");
      welcome();
      break;
    default:
    {
      cout << "Pilihan anda tidak valid!\n";
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      system("cls");
      menuStaff();
    }
  }
}

Pelanggan pelanggan;

void Tampilan::menuPelanggan() {
  system("Color 0B");
  char pilihan;
  int nomorMeja;
  menu:
    system("cls");
    cout << "HALAMAN PELANGGAN...\n";
    cout << "1. Tampilkan menu restoran\n";
    cout << "2. Pesan makanan\n";
    cout << "3. Tampilkan bill atau tagihan\n";
    cout << "4. Bayar bill atau tagihan\n";
    cout << "5. Kembali ke menu sebelumnya\n";
    cout << "Masukkan pilihan anda: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case '1':
      pelanggan.menuHariIni();
      cout << "Menu berhasil ditambahkan\n";
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      goto menu;
    case '2':
      pelanggan.pemesanan();
      break;
    case '3':
      cout << "Masukkan nomor meja anda: ";
      cin >> nomorMeja;
      while (!pelanggan.validasiMeja(nomorMeja))
      {
        cout << "\nMeja tersebut kosong! Tidak ada riwayat bill!\n Masukkan nomor meja yang valid: ";
        cin >> nomorMeja;
      }
      pelanggan.bill(nomorMeja);
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      menuPelanggan();
      break;
    case '4':
      cout << "Masukkan nomor meja anda: ";
      cin >> nomorMeja;
      while (!pelanggan.validasiMeja(nomorMeja))
      {
        cout << "\nMeja tersebut kosong! Tidak ada riwayat bill!\n Masukkan nomor meja yang valid: ";
        cin >> nomorMeja;
      }
      pelanggan.bayar(nomorMeja);
      break;
    case '5':
      system("cls");
      welcome();
      break;
    default:
    {
      cout << "Pilihan anda tidak valid!\n";
      cout << "Tekan tombol apapun untuk melanjutkan...\n";
      getch();
      system("cls");
      menuPelanggan();
    }
  }
}

bool Pelanggan::validasiMeja(int meja)
{
  data = 0;
  Pelanggan *temp;
  temp = headPelanggan;
  bool hasil = false;

  while (temp != NULL)
  {
    data++;
    if (temp->nomorMeja ==  meja)
    {
      hasil = true;
      break;
    }
    temp = temp->next;
  }
  return hasil;
}

void Pelanggan::pemesanan()
{
  Tampilan t;
  char pilihan;
  string nama;
  int noMeja;
  int idPemesanan;
  cout<<"================FORM PEMESANAN==============\n\n";
  cout << "Masukkan nama anda: ";
  cin >> ws;
  getline(cin, nama);
  cout << "Masukkan nomor meja yang anda pilih: ";
  cin >> noMeja;
  while (validasiMeja(noMeja))
  {
    cout << "\nMeja telah ditempati!\nMasukkan nomor meja lain: ";
    cin >> noMeja;
  }
  pelanggan.menuHariIni();
  int i = 0;
  cout << "\nMasukkan id makanan yang ingin anda pesan: ";
  cin >> idPemesanan;

  Pelanggan* newNode = new Pelanggan(nama, noMeja, idPemesanan);

  if (headPelanggan == NULL)
  {
    order++;
    headPelanggan = newNode;
  }
  else
  {
    Pelanggan *temp = headPelanggan;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newNode;
    order++;
  }

  cout << "Tekan tombol apapun untuk melanjutkan...\n";
  getch();
  t.menuPelanggan();
}

int Pelanggan::bill(int meja)
{
  float totalHarga = 0, ppn = 0;
  int totalTagihan;
  Tagihan t1(0);
  Pelanggan *temp;
  Menu *temp2;
  temp = headPelanggan;
  temp2 = head;
  while (temp != NULL)
  {
    if (temp->nomorMeja == meja)
    {
      cout << "\nNama Pelanggan: " << temp->namaPelanggan;
      cout << "\nNomor Meja: " << temp->nomorMeja << "\n";
      cout << "\n\t\tBill atau Tagihan: \n\n";
      cout << "\t---------------------------------------------\n";
      cout << "\t|\tNama Item\t\tHarga(Rp.)   |\n";
      cout << "\t---------------------------------------------\n";
      while (temp2 != NULL)
      {
        if (temp->idPemesanan == temp2->idItem)
        {
          cout << "\t|\t" << temp2->namaItem << "\t\t\t" << temp2->hargaItem << "\t     |\n";
          Tagihan t2(temp2->hargaItem * 0.1);
          t1 = t1 + t2;
          ppn = t1.t;
          totalTagihan = round(temp2->hargaItem + ppn);
        }
        temp2 = temp2->next;
      }
      temp = temp->next;
    }
  }
  cout << "\n\t|\tPPn (10%)\t\t" << ppn << "          |\n";
  cout << "\t---------------------------------------------";
  cout << "\n\t|\tHarga Setelah PPn\t\t" << totalTagihan << " |\n";
  cout << "\t---------------------------------------------\n\n";

  return totalTagihan;
}

void Pelanggan::bayar(int meja)
{
  Tampilan t;
  int ketemu = 0;
  float kembalian = 0, tagihan, tagihanDibayar;
  Pelanggan *temp;
  temp = headPelanggan;
  while (temp != NULL)
  {
    if (meja == temp->nomorMeja)
    {
      tagihan = bill(meja);
      do
      {
        cout << "\n\nJumlah yang harus dibayarkan adalah Rp. " << tagihan;
        cout << "\nMasukkan nominal yang anda bayarkan: Rp.";
        cin >> tagihanDibayar;
        if (tagihanDibayar > tagihan)
        {
          kembalian = tagihanDibayar - tagihan;
          cout << "\nRp. " << tagihan << " telah dibayar. Terima kasih! Ini kembalian anda Rp." << kembalian;
          tagihanDibayar = tagihan;
        }
        else if (tagihanDibayar < tagihan)
        {
          kembalian = tagihan - tagihanDibayar;
          cout << "\nRp. " << tagihan << " telah dibayar. Pembayaran kurang, mohon bayar Rp." << kembalian << " lagi";
          tagihan = kembalian;
        }
        else
        {
          cout << "\nRp. " << tagihan << " telah dibayar. Terima kasih!";
        }
      } while (tagihanDibayar != tagihan);
      ketemu = 1;
    }
    temp = temp->next;
  }

  if (!ketemu)
  {
    cout << "\nTidak ditemukan meja dengan nomor meja: " << meja;
  }

  if (ketemu == 1)
  {
    cout << "\n\nTerima kasih telah berkunjung ke restoran kami!\n\n";
    exit(0);
  }
  cout << "\nTekan tombol apapun untuk melanjutkan...\n";
  getch();
  system("cls");
  t.menuPelanggan();
}

void Tampilan::awal()
{
  system("cls");
  cout << endl
       << endl
       << endl
       << endl
       << endl;
  cout << "\t\t\t\t******************************************************** \n";
  cout << "\t\t\t\t\t\t Selamat Datang di Restaurant \n";
  cout << "\t\t\t\t******************************************************** \n";
  cout << "\n\n\n\t\t\t\t\t Tekan tombol apapun untuk melanjutkan...\n";
  getch();
  system("cls");
}


void Tampilan::tipePengguna()
{
  cout << "Pilih tipe pengguna \n";
  cout << "1. Staff \n";
  cout << "2. Pelanggan \n";
  cout << "3. Exit \n";
}

void Tampilan::loginStaff()
{
  string id;
  string pass;
  bool masuk=false;
  while (!masuk)
  {
    cout<<"=================MASUK STAFF==============\n\n";//ID : admin, Password : admin
    cout<<"Masukkan ID : ";
    cin>>id;
    cout<<"Masukkan Password : ";
    cin>>pass;
    UserBaru ub;
    masuk = ub.cek(id,pass);
    if(!masuk)
    {
      cout<<"Anda Salah Input ID/Password!\n";
    }
    else
    {
      id = ub.cek(id,pass);
    }
  }
}

void Tampilan::welcome()
{
  char pilihan;
  tipePengguna();
  cout << "Masukkan pilihan anda: ";
  cin >> pilihan;

  switch (pilihan)
  {
  case '1':
    loginStaff();
    menuStaff();
    break;
  case '2':
    menuPelanggan();
    break;
  case '3':
    cout << "\n\nTerima kasih telah berkunjung ke restaurant kami!\n\n";
    exit(0);
    break;
  default:
  {
    cout << "Pilihan anda tidak valid!\n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    system("cls");
    welcome();
  }
  }
}

int main() {
  system("Color 0B");
  Tampilan t;
  t.awal();
  t.welcome();
  getch();
  return 0;
}
