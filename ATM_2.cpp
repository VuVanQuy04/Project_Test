#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <graphics.h>
using namespace std;

// Ham them dau cham phan cach cho so tien
string themDauCham(string so) {
    string ketQua = "";
    int dem = 0;
    for (int i = so.length() - 1; i >= 0; i--) {
        dem++;
        ketQua = so[i] + ketQua;
        if (dem % 3 == 0 && i != 0) {
            ketQua = "." + ketQua;
        }
    }
    return ketQua;
}

class QuanLyPin {
public:
    string pin;
    int soLanThu = 0;

    QuanLyPin() {
        ifstream file("pin.txt");
        if (file.is_open()) {
            getline(file, pin);
            file.close();
        } else {
            pin = "1234";
        }
    }

    bool xacNhanPin() {
        string nhapPin = "";
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        outtextxy(100, 100, "Nhap ma PIN: ");
        
        while (soLanThu < 3) {
            char key = getch();
            if (key == 13) { // Phim Enter
                if (nhapPin == pin) {
                    cleardevice();
                    outtextxy(100, 100, "Xac nhan thanh cong!");
                    delay(2000);
                    return true;
                } else {
                    soLanThu++;
                    cleardevice();
                    outtextxy(100, 100, "Sai PIN! Con ");
                    stringstream ss;
                    ss << (3 - soLanThu);
                    outtextxy(300, 100, const_cast<char*>(ss.str().c_str()));
                    outtextxy(350, 100, " lan thu.");
                    delay(2000);
                    cleardevice();
                    outtextxy(100, 100, "Nhap ma PIN: ");
                    nhapPin = "";
                }
            } else if (key == 8 && !nhapPin.empty()) { // Phim Backspace
                nhapPin.erase(nhapPin.length() - 1, 1);
                cleardevice();
                outtextxy(100, 100, "Nhap ma PIN: ");
                outtextxy(350, 100, const_cast<char*>(nhapPin.c_str()));
            } else if (isdigit(key) && nhapPin.length() < 9) {
                nhapPin += key;
                cleardevice();
                outtextxy(100, 100, "Nhap ma PIN: ");
                outtextxy(350, 100, const_cast<char*>(nhapPin.c_str()));
            }
        }
        cleardevice();
        outtextxy(100, 100, "Nhap sai 3 lan. The bi khoa!");
        delay(2000);
        return false;
    }

    void doiPin() {
        string pinCu = "", pinMoi = "";
        cleardevice();
        outtextxy(100, 100, "Nhap PIN cu: ");
        
        while (true) {
            char key = getch();
            if (key == 13) break;
            if (key == 8 && !pinCu.empty()) {
                pinCu.erase(pinCu.length() - 1, 1);
            } else if (isdigit(key) && pinCu.length() < 9) {
                pinCu += key;
            }
            cleardevice();
            outtextxy(100, 100, "Nhap PIN cu: ");
            outtextxy(350, 100, const_cast<char*>(pinCu.c_str()));
        }

        if (pinCu == pin) {
            cleardevice();
            outtextxy(100, 100, "Nhap PIN moi: ");
            while (true) {
                char key = getch();
                if (key == 13) break;
                if (key == 8 && !pinMoi.empty()) {
                    pinMoi.erase(pinMoi.length() - 1, 1);
                } else if (isdigit(key) && pinMoi.length() < 9) {
                    pinMoi += key;
                }
                cleardevice();
                outtextxy(100, 100, "Nhap PIN moi: ");
                outtextxy(350, 100, const_cast<char*>(pinMoi.c_str()));
            }
            pin = pinMoi;
            ofstream file("pin.txt");
            file << pin;
            file.close();
            cleardevice();
            outtextxy(100, 100, "Doi PIN thanh cong!");
            delay(2000);
        } else {
            cleardevice();
            outtextxy(100, 100, "PIN cu khong dung!");
            delay(2000);
        }
    }
};

class QuanLySoDu {
public:
    double soDu;

    QuanLySoDu() {
        ifstream file("sodu.txt");
        if (file.is_open()) {
            file >> soDu;
            file.close();
        } else {
            soDu = 5000000;
        }
    }

    void capNhatSoDu(double soTien) {
        soDu += soTien;
        ofstream file("sodu.txt");
        file << soDu;
        file.close();
    }

    void xemSoDu() {
        cleardevice();
        outtextxy(100, 100, "So du hien tai: ");
        stringstream ss;
        ss << fixed << setprecision(0) << soDu;
        string soDuStr = themDauCham(ss.str()) + " VND";
        outtextxy(350, 100, const_cast<char*>(soDuStr.c_str()));
        delay(3000);
    }
};

class LichSuGiaoDich {
public:
    void luuGiaoDich(string noiDung) {
        ofstream file("lichsugiaodich.txt", ios::app);
        time_t now = time(0);
        string dt = ctime(&now);
        if (!dt.empty() && dt[dt.length() - 1] == '\n') {
            dt.erase(dt.length() - 1);
        }
        file << dt << " - " << noiDung << "\n";
        file.close();
    }

    void xemLichSu() {
        ifstream file("lichsugiaodich.txt");
        string line;
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        outtextxy(100, 100, "Lich su giao dich:");
        int y = 150;
        const int maxKyTuMoiDong = 70;

        while (getline(file, line)) {
            int viTri = 0;
            while (viTri < (int)line.length()) {
                string dongHienTai = line.substr(viTri, maxKyTuMoiDong);
                outtextxy(100, y, const_cast<char*>(dongHienTai.c_str()));
                y += 30;
                viTri += maxKyTuMoiDong;
            }
            y += 10;
        }
        file.close();
        delay(5000);
    }
};

class RutTien {
public:
    void thucHienRutTien(QuanLySoDu &soDu, LichSuGiaoDich &ls) {
        string soTienStr = "";
        cleardevice();
        outtextxy(100, 100, "Nhap so tien: ");
        
        while (true) {
            char key = getch();
            if (key == 13) break;
            if (key == 8 && !soTienStr.empty()) {
                soTienStr.erase(soTienStr.length() - 1, 1);
            } else if (isdigit(key) && soTienStr.length() < 19) {
                soTienStr += key;
            }
            cleardevice();
            outtextxy(100, 100, "Nhap so tien: ");
            string soTienHienThi = themDauCham(soTienStr);
            outtextxy(350, 100, const_cast<char*>(soTienHienThi.c_str()));
        }

        double soTien = atof(soTienStr.c_str()); // Thay stod b?ng atof
        if (soTien > 0 && soTien <= soDu.soDu) {
            soDu.capNhatSoDu(-soTien);
            cleardevice();
            outtextxy(100, 100, "Rut tien thanh cong!");
            stringstream ss;
            ss << fixed << setprecision(0) << soDu.soDu;
            string soDuStr = "So du: " + themDauCham(ss.str()) + " VND";
            outtextxy(100, 150, const_cast<char*>(soDuStr.c_str()));
            stringstream lichSu;
            ss.str(""); // Xoa noi dung cu cua stringstream
            ss << fixed << setprecision(0) << soTien;
            lichSu << "Rut tien: " << themDauCham(ss.str()) + " VND";
            ls.luuGiaoDich(lichSu.str());
            delay(2000);
        } else {
            cleardevice();
            outtextxy(100, 100, "So tien khong hop le!");
            delay(2000);
        }
    }
};

class ChuyenKhoan {
public:
    void thucHienChuyenKhoan(QuanLySoDu &soDu, LichSuGiaoDich &ls) {
        string soTienStr = "", taiKhoan = "", noiDung = "";
        int chon;
        vector<string> nganHangs;
        nganHangs.push_back("MB Bank");
        nganHangs.push_back("Techcombank");
        nganHangs.push_back("Vietinbank");
        nganHangs.push_back("Vietcombank");

        cleardevice();
        outtextxy(100, 100, "Nhap so tien: ");
        while (true) {
            char key = getch();
            if (key == 13) break;
            if (key == 8 && !soTienStr.empty()) {
                soTienStr.erase(soTienStr.length() - 1, 1);
            } else if (isdigit(key) && soTienStr.length() < 19) {
                soTienStr += key;
            }
            cleardevice();
            outtextxy(100, 100, "Nhap so tien: ");
            string soTienHienThi = themDauCham(soTienStr);
            outtextxy(350, 100, const_cast<char*>(soTienHienThi.c_str()));
        }
        double soTien = atof(soTienStr.c_str()); // Thay stod b?ng atof

        cleardevice();
        outtextxy(100, 100, "Chon ngan hang:");
        for (size_t i = 0; i < nganHangs.size(); i++) {
            stringstream ss;
            ss << (i + 1);
            string buffer = ss.str() + ". " + nganHangs[i];
            outtextxy(100, 150 + i * 30, const_cast<char*>(buffer.c_str()));
        }
        chon = getch() - '0';
        if (chon < 1 || chon > (int)nganHangs.size()) {
            cleardevice();
            outtextxy(100, 100, "Lua chon khong hop le!");
            delay(2000);
            return;
        }
        string nganHang = nganHangs[chon - 1];

        cleardevice();
        outtextxy(100, 100, "Nhap so tai khoan: ");
        while (true) {
            char key = getch();
            if (key == 13) break;
            if (key == 8 && !taiKhoan.empty()) {
                taiKhoan.erase(taiKhoan.length() - 1, 1);
            } else if (isdigit(key) && taiKhoan.length() < 19) {
                taiKhoan += key;
            }
            cleardevice();
            outtextxy(100, 100, "Nhap so tai khoan: ");
            outtextxy(350, 100, const_cast<char*>(taiKhoan.c_str()));
        }

        cleardevice();
        outtextxy(100, 100, "Nhap noi dung: ");
        while (true) {
            char key = getch();
            if (key == 13) break;
            if (key == 8 && !noiDung.empty()) {
                noiDung.erase(noiDung.length() - 1, 1);
            } else if (noiDung.length() < 49) {
                noiDung += key;
            }
            cleardevice();
            outtextxy(100, 100, "Nhap noi dung: ");
            outtextxy(350, 100, const_cast<char*>(noiDung.c_str()));
        }

        if (soTien > 0 && soTien <= soDu.soDu) {
            soDu.capNhatSoDu(-soTien);
            cleardevice();
            outtextxy(100, 100, "Chuyen khoan thanh cong!");
            stringstream ss;
            ss << fixed << setprecision(0) << soTien;
            string chuyenKhoanStr = themDauCham(ss.str()) + " VND den " + taiKhoan;
            outtextxy(100, 150, const_cast<char*>(chuyenKhoanStr.c_str()));
            outtextxy(100, 200, const_cast<char*>(nganHang.c_str()));
            stringstream lichSu;
            lichSu << "Chuyen khoan: " << themDauCham(ss.str()) + " VND den " << taiKhoan << " - " << nganHang << " - Noi dung: " << noiDung;
            ls.luuGiaoDich(lichSu.str());
            delay(2000);
        } else {
            cleardevice();
            outtextxy(100, 100, "So tien khong hop le!");
            delay(2000);
        }
    }
};

void veMenu() {
    cleardevice();
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    outtextxy(400, 50, "MENU DICH VU");

    rectangle(300, 150, 700, 200);
    outtextxy(350, 170, "1. Doi PIN");

    rectangle(300, 220, 700, 270);
    outtextxy(350, 240, "2. Rut tien");

    rectangle(300, 290, 700, 340);
    outtextxy(350, 310, "3. Xem so du");

    rectangle(300, 360, 700, 410);
    outtextxy(350, 380, "4. Chuyen khoan");

    rectangle(300, 430, 700, 480);
    outtextxy(350, 450, "5. Xem lich su");

    rectangle(300, 500, 700, 550);
    outtextxy(350, 520, "6. Thoat");
}

int main() {
    QuanLyPin qlp;
    QuanLySoDu soDu;
    RutTien rt;
    ChuyenKhoan ck;
    LichSuGiaoDich ls;

    initwindow(1024, 768, "ATM - Giao dien do hoa");

    if (!qlp.xacNhanPin()) {
        closegraph();
        return 0;
    }

    int luaChon;
    do {
        veMenu();
        luaChon = getch() - '0';
        switch (luaChon) {
            case 1:
                qlp.doiPin();
                break;
            case 2:
                rt.thucHienRutTien(soDu, ls);
                break;
            case 3:
                soDu.xemSoDu();
                break;
            case 4:
                ck.thucHienChuyenKhoan(soDu, ls);
                break;
            case 5:
                ls.xemLichSu();
                break;
            case 6:
                cleardevice();
                outtextxy(100, 100, "Thoat. Cam on ban!");
                delay(2000);
                break;
            default:
                cleardevice();
                outtextxy(100, 100, "Lua chon khong hop le!");
                delay(2000);
        }
    } while (luaChon != 6);

    closegraph();
    return 0;
}
