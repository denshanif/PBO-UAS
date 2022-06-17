#include <iostream>
#include <conio.h>

using namespace std;

class Tampilan;
class Staff;
class Menu;

Menu *head;

int data = 0;

class Tampilan {
  public:
    void awal();
    void tipePengguna();
    void welcome();
    void menuStaff();
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
      while (temp != NULL) {
        data++;
        cout << "   ID : " << temp->idItem << endl;
        cout << "   Nama : " << temp->namaItem << endl;
        cout << "   Harga : Rp." << temp->hargaItem << "\n\n" << endl;

        temp = temp->next;
      }
      cout << "\n===========================================\n\n";
      cout << "Jumlah Item Pada Menu: " << data << endl;
    }
};

Menu menu;

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

        Menu *newNode = new Menu(id, nama, harga);

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

Staff staff;

void Tampilan::menuStaff() {
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
  cout << "2. Exit \n";
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
    menuStaff();
    break;
  case '2':
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
  Tampilan t;
  t.awal();
  t.welcome();
  getch();
  return 0;
}