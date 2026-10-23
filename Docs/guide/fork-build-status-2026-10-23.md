# 372dragon fork — build results (23/10/2026)

Repository: `nguyentrieu210/372dragon`; work branch `fix/skynet-framework-build`.

## Server Linux x86-64 — build PASS (chưa chạy game)

- Khôi phục đúng 27 file Skynet core bị thiếu từ upstream [cloudwu/skynet v1.4.0](https://github.com/cloudwu/skynet/tree/v1.4.0) (MIT); giữ nguyên file tùy biến đã có.
- Lua 5.4 (bundled): PASS.
- Skynet: PASS cả bản kiểm thử `linux_nojemalloc` và bản Linux chuẩn `linux` dùng jemalloc 5.2.1 với `--with-jemalloc-prefix=je_`.
- Module C/C++ của GameServer: PASS.
- `ldd` trên binary Skynet: không có `not found`.
- [GitHub Actions build chuẩn có jemalloc — PASS](https://github.com/nguyentrieu210/372dragon/actions/runs/39987884252).
- Đã thử build trên Codespace Ubuntu 24.04 x86-64. Giữ file tạo ra trên Codespace nhưng không commit thư viện .a.
- Cảnh báo C/C++ cũ và OpenSSL 3 còn tồn tại; chưa chứng minh an toàn/đầy đủ khi chạy thật.

## Client Windows MSVC 2022 x64 — Game.exe build PASS (chưa chơi được)

- [GitHub Actions: build `Game.exe` thành công](https://github.com/nguyentrieu210/372dragon/actions/runs/39986709054).
- Đã xác minh 1 file `Game.exe` trong output, SHA256:
  `92A3E5910E6CB9A1D6D48B8DF74AB74FDC9318B3A77B75024238E91654C3830E`.
- Đã bổ sung `Src/Engine/Interface/TDGameInterface.h` do dự án tự tái tạo khai báo interface từ `CGameInterface` và chuẩn hóa tên include tương ứng. Lần CI PASS được ghi ở trên là từ trước thay đổi này, khi dùng header lịch sử chỉ trong runner tạm; cần xem lần CI tiếp theo để xác nhận header mới.
- D3DX9 x64 dùng gói [Microsoft.DXSDK.D3DX 9.29.952.8](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX), tải vào runner; không copy thư viện nhị phân vào Git.
- FMOD Core SDK 2.02.35 chưa có. CMake hiện có silent fallback khi thiếu FMOD, vì vậy build qua không chứng minh âm thanh hoạt động.
- `Game.exe` chưa được đóng gói làm bản phát hành; render/UI DLL, launcher, Cg, runtime và data chưa được nghiệm thu.
- Workflow đã bổ sung bước kiểm tra build plugin `cys_wxrender` và `cys_uisystem` sau khi Game.exe compile.

## Còn thiếu để có bản chơi thử 1 người

1. Build đầy đủ `Render.dll`, `UI_CEGUI.dll`, các DLL phụ thuộc; kiểm đúng bản executable + SDK/giấy phép.
2. Tạo bộ client Windows có launcher/config/plugin và data hợp lệ; không dùng binary vô danh từ Internet.
3. Dựng database MongoDB 4.4.31 / MQTT và script/scene dữ liệu riêng trên Linux; chỉ cấu hình localhost nếu test nội bộ.
4. Thử login, tạo nhân vật, vào Đại Lý, điều khiển, thoát và đăng nhập lại; lưu log và kết quả trước khi tuyên bố game chạy được.
5. Chưa có căn cứ để phát hành binary hoặc data TLBB kế thừa công khai.

**Quy ước:** CI compile PASS không đồng nghĩa game runtime PASS. Không merge `main` hay công bố gói chơi cho tới khi nghiệm thu đủ.

## Blocker runtime mới phát hiện

- `Server/GameServer/main.lua` gọi `license_check.check_or_abort()`; module này `require('llicense')`.
- Trong Codespace snapshot đang chạy, không tìm thấy native module `llicense` để load. Khi `require` thất bại, chương trình gọi `skynet.abort()`. Vì vậy **build server PASS chưa đồng nghĩa server khởi động được**.
- Cần tìm thành phần runtime/giấy phép hợp lệ từ nhà cung cấp để kiểm thử, không tự vô hiệu hóa kiểm tra.
