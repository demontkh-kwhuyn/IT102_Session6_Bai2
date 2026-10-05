#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char maPhieu[MAX][15];
    char tenSach[MAX][50];
    int soNgayMuon[MAX];
    int tienPhat[MAX];
    int soLuong = 0;
    int choice;

    do {
        printf("\n================ HỆ THỐNG QUẢN LÝ MƯỢN TRẢ SÁCH (LIBRARY_WMS) ================\n");
        printf("1. Thêm lượt mượn sách mới\n");
        printf("2. Hiển thị danh sách mượn sách\n");
        printf("3. Cập nhật số ngày mượn theo Mã phiếu\n");
        printf("4. Xóa lượt mượn sách theo Mã phiếu\n");
        printf("5. Thống kê danh sách phiếu mượn bị phạt (Quá hạn > 14 ngày)\n");
        printf("6. Thoát chương trình\n");
        printf("==============================================================================\n");
        printf("Lựa chọn của bạn: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                if (soLuong >= MAX) {
                    printf("Hệ thống đầy, không thể thêm phiếu mượn mới!\n");
                    break;
                }

                char tempMa[15];
                int trungLap = 0;
                do {
                    trungLap = 0;
                    printf("Nhập mã phiếu mượn: ");
                    scanf("%14s", tempMa);
                    while (getchar() != '\n');

                    for (int i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], tempMa) == 0) {
                            trungLap = 1;
                            printf("Mã phiếu đã tồn tại! Vui lòng nhập mã khác.\n");
                            break;
                        }
                    }
                } while (trungLap);

                strcpy(maPhieu[soLuong], tempMa);

                printf("Nhập tên sách: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                size_t len = strlen(tenSach[soLuong]);
                if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                    tenSach[soLuong][len - 1] = '\0';
                }

                int ngay;
                do {
                    printf("Nhập số ngày mượn thực tế: ");
                    if (scanf("%d", &ngay) != 1) {
                        ngay = 0;
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');
                    if (ngay <= 0) {
                        printf("Số ngày mượn phải lớn hơn 0. Vui lòng nhập lại!\n");
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;
                tienPhat[soLuong] = (ngay > 14) ? (ngay - 14) * 5000 : 0;

                soLuong++;
                printf("Thêm lượt mượn sách thành công!\n");
                break;
            }
            case 2: {
                if (soLuong == 0) {
                    printf("Danh sách mượn sách hiện đang rỗng!\n");
                    break;
                }

                printf("\n================================ DANH SÁCH MƯỢN SÁCH ================================\n");
                printf("%-3s | %-10s | %-30s | %-8s | %-15s\n", "STT", "Mã Phiếu", "Tên Sách", "Số Ngày", "Tiền Phạt (VNĐ)");
                printf("-------------------------------------------------------------------------------------\n");
                int tongTienPhat = 0;
                for (int i = 0; i < soLuong; i++) {
                    printf("%-3d | %-10s | %-30s | %-8d | %-15d\n", i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    tongTienPhat += tienPhat[i];
                }
                printf("-------------------------------------------------------------------------------------\n");
                printf("Tổng tiền phạt toàn hệ thống: %d VNĐ\n", tongTienPhat);
                break;
            }
            case 3: {
                char maCanSua[15];
                printf("Nhập mã phiếu mượn cần cập nhật: ");
                scanf("%14s", maCanSua);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maCanSua) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Không tìm thấy phiếu mượn có mã: %s\n", maCanSua);
                } else {
                    printf("Tìm thấy phiếu mượn của sách: %s (Số ngày hiện tại: %d)\n", tenSach[index], soNgayMuon[index]);
                    int ngayMoi;
                    do {
                        printf("Nhập số ngày mượn thực tế mới: ");
                        if (scanf("%d", &ngayMoi) != 1) {
                            ngayMoi = 0;
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n');
                        if (ngayMoi <= 0) {
                            printf("Số ngày mượn phải lớn hơn 0. Vui lòng nhập lại!\n");
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[index] = ngayMoi;
                    tienPhat[index] = (ngayMoi > 14) ? (ngayMoi - 14) * 5000 : 0;
                    printf("Cập nhật số ngày mượn thành công!\n");
                }
                break;
            }
            case 4: {
                char maCanXoa[15];
                printf("Nhập mã phiếu mượn cần xóa: ");
                scanf("%14s", maCanXoa);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maCanXoa) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Không tìm thấy phiếu mượn có mã: %s\n", maCanXoa);
                } else {
                    for (int i = index; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }
                    soLuong--;
                    printf("Xóa phiếu mượn thành công!\n");
                }
                break;
            }
            case 5: {
                int count = 0;
                printf("\n============================= DANH SÁCH PHIẾU QUÁ HẠN =============================\n");
                printf("%-3s | %-10s | %-30s | %-8s | %-15s\n", "STT", "Mã Phiếu", "Tên Sách", "Số Ngày", "Tiền Phạt (VNĐ)");
                printf("-------------------------------------------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > 14) {
                        count++;
                        printf("%-3d | %-10s | %-30s | %-8d | %-15d\n", count, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    }
                }
                printf("-------------------------------------------------------------------------------------\n");
                if (count == 0) {
                    printf("Không có lượt mượn nào bị quá hạn phạt!\n");
                }
                break;
            }
            case 6:
                printf("Thoát chương trình. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại!\n");
        }
    } while (choice != 6);

    return 0;
}