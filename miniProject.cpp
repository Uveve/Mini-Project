#include <iostream>
using namespace std;

struct room {
    string jenis;
    int price;
    int status;
};

struct guest {
    string nama;
    string id;
    int roomIndex;
    int durasi;
    int totalKamar;
    string makanan;
    int hargaMakanan;
};

room hotelRooms[5] = {
    {"Standard", 500000, 1},
    {"Superior", 750000, 1},
    {"Deluxe", 1200000, 1},
    {"Executive", 2500000, 1},
    {"Presidential", 7500000, 1}
};

guest tamu[100];
int tamuCount = 0;

int reservasi() {
    int roomChoice, counter, index;

    cout << "Pilih Jenis kamar: " << endl;
    cout << "1. Standard Room" << endl;
    cout << "2. Superior Room" << endl;
    cout << "3. Deluxe Room" << endl;
    cout << "4. Executive Room" << endl;
    cout << "5. Presidential Room" << endl;
    cout << "Masukan pilihan kamar: ";
    cin >> roomChoice;

    switch(roomChoice) {
        case 1: index = 0; break;
        case 2: index = 1; break;
        case 3: index = 2; break;
        case 4: index = 3; break;
        case 5: index = 4; break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return reservasi();
    }

    cout << hotelRooms[index].jenis << endl;
    cout << "Rp " << hotelRooms[index].price << "/malam" << endl;

    if (hotelRooms[index].status == 1) {
        cout << "Status: Tersedia" << endl;

        cin.ignore();
        cout << "Masukan Nama: ";
        getline(cin, tamu[tamuCount].nama);
        cout << "Masukan Nomor Identitas: ";
        getline(cin, tamu[tamuCount].id);
        cout << "Masukan Durasi Menginap (malam): ";
        cin >> counter;

        int total = hotelRooms[index].price * counter;

        cout << "\n--- Detail Reservasi ---" << endl;
        cout << "Nama: " << tamu[tamuCount].nama << endl;
        cout << "Nomor Identitas: " << tamu[tamuCount].id << endl;
        cout << "Tipe Kamar: " << hotelRooms[index].jenis << endl;
        cout << "Lama Menginap: " << counter << " malam" << endl;
        cout << "Harga Total: Rp " << total << endl;
        cout << "Nomor Kamar: " << index + 1 << endl;

        tamu[tamuCount].roomIndex = index;
        tamu[tamuCount].durasi = counter;
        tamu[tamuCount].totalKamar = total;
        tamu[tamuCount].makanan = "-";
        tamu[tamuCount].hargaMakanan = 0;
        tamuCount++;

        hotelRooms[index].status = 0;
        cout << "Reservasi Berhasil!" << endl;
    } else {
        cout << "Status: Tidak Tersedia, silahkan pilih kamar lain" << endl;
        return reservasi();
    }
    return 0;
}

int launch() {
    string menuList[9] = {
        "Nasi Goreng", "Mie Goreng", "Ayam Bakar",
        "Burger", "Pasta", "Es Teh",
        "Kopi", "Jus Jeruk", "Air Mineral"
    };
    int hargaList[9] = {
        35000, 30000, 45000,
        40000, 50000, 8000,
        15000, 18000, 5000
    };

    cout << "\n--- Daftar Menu Makanan & Minuman ---" << endl;
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << ". " << menuList[i] << " - Rp " << hargaList[i] << endl;
    }

    int menuChoice, qty, roomNumber;
    string namaCari;

    cout << "\nMasukan pilihan menu: ";
    cin >> menuChoice;

    if (menuChoice < 1 || menuChoice > 9) {
        cout << "Menu tidak valid!" << endl;
        return launch();
    }

    cout << "Masukan jumlah: ";
    cin >> qty;

    if (qty <= 0) {
        cout << "Jumlah tidak valid!" << endl;
        return launch();
    }

    int totalHarga = hargaList[menuChoice - 1] * qty;

    cin.ignore();
    cout << "Masukan nama tamu: ";
    getline(cin, namaCari);
    cout << "Masukan nomor kamar: ";
    cin >> roomNumber;

    int found = -1;
    for (int i = 0; i < tamuCount; i++) {
        if (tamu[i].nama == namaCari && tamu[i].roomIndex == roomNumber - 1) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        cout << "Data tamu tidak ditemukan!" << endl;
        return 0;
    }

    tamu[found].makanan = menuList[menuChoice - 1];
    tamu[found].hargaMakanan = totalHarga;

    cout << "\n--- Detail Pesanan ---" << endl;
    cout << "Menu: " << menuList[menuChoice - 1] << endl;
    cout << "Jumlah: " << qty << endl;
    cout << "Total: Rp " << totalHarga << endl;
    cout << "Pesanan makanan berhasil ditambahkan!" << endl;
    return 0;
}

int invoice() {
    string keyword;
    int roomNumber;

    cin.ignore();
    cout << "Masukan nomor identitas tamu: ";
    getline(cin, keyword);
    cout << "Masukan nomor kamar (0 jika tidak tahu): ";
    cin >> roomNumber;

    int found = -1;
    for (int i = 0; i < tamuCount; i++) {
        bool matchId = (tamu[i].id == keyword);
        bool matchRoom = (roomNumber > 0 && tamu[i].roomIndex == roomNumber - 1);
        if (matchId || matchRoom) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        cout << "Data tidak ditemukan!" << endl;
        return 0;
    }

    int totalBiaya = tamu[found].totalKamar + tamu[found].hargaMakanan;

    cout << "\n========== INVOICE ==========" << endl;
    cout << "Nama Tamu       : " << tamu[found].nama << endl;
    cout << "Nomor identitas : " << tamu[found].id << endl;
    cout << "Tipe Kamar      : " << hotelRooms[tamu[found].roomIndex].jenis << endl;
    cout << "Durasi Menginap : " << tamu[found].durasi << " malam" << endl;
    cout << "Total Kamar     : Rp " << tamu[found].totalKamar << endl;
    cout << "Pesanan Makan   : " << tamu[found].makanan << endl;
    cout << "Total Makanan   : Rp " << tamu[found].hargaMakanan << endl;
    cout << "-------------------------------" << endl;
    cout << "TOTAL BIAYA     : Rp " << totalBiaya << endl;
    cout << "===============================" << endl;
    return 0;
}

int menu() {
    int menuChoice;
    cout << "\nSelamat datang" << endl;
    cout << "Pilihan menu" << endl;
    cout << "1. Reservasi" << endl;
    cout << "2. Pesan Makan" << endl;
    cout << "3. Invoice" << endl;
    cout << "4. Keluar" << endl;
    cout << "Masukan pilihan anda: ";
    cin >> menuChoice;

    switch(menuChoice) {
        case 1:
            reservasi();
            break;
        case 2:
            launch();
            break;
        case 3:
            invoice();
            break;
        case 4:
            cout << "Terima kasih telah menggunakan layanan kami." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
    return menu();
}

int main() {
    menu();
    return 0;
}
