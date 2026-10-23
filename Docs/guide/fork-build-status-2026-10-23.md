# TLBB 372dragon — kết quả build trên fork (23/10/2026)

Fork: `nguyentrieu210/372dragon`; nhánh thử `fix/skynet-framework-build`.

## Linux (GitHub Codespaces, Ubuntu 24.04, x86-64)

- Nguồn `Server/GameServer/framework/skynet-src/` thiếu 27 file lõi.
- Đã lấy **chỉ các file còn thiếu** từ tag `v1.4.0` (`4faa6499e819e4b5463d0b1efda7cf9d9f6dabcc`) của [cloudwu/skynet](https://github.com/cloudwu/skynet), theo giấy phép MIT; giữ các file tùy biến hiện có.
- `make -C Server/GameServer/framework/3rd/lua linux -j2`: PASS.
- `make -C Server/GameServer/framework linux_nojemalloc -j2`: PASS.
- `make -C Server/GameServer -j2`: PASS.
- Binary `Server/GameServer/framework/skynet` là ELF x86-64 và `ldd` không thấy `not found` tại môi trường đã test.
- **Giới hạn:** `linux_nojemalloc` là bản kiểm tra kỹ thuật, **không thay thế** build Linux chính thức với jemalloc; chưa thử bật server đầy đủ và đăng nhập, còn thiếu data/server configs, MongoDB và MQTT. Một số lỗi cảnh báo C++/OpenSSL cũ còn tồn tại.
- Workflow kiểm tra trên GitHub: [Linux server compile check](https://github.com/nguyentrieu210/372dragon/actions/workflows/linux-server-build.yml).

## Windows (GitHub Actions, windows-2022)

Lần kiểm tra: [Run 39983919852](https://github.com/nguyentrieu210/372dragon/actions/runs/39983919852).

- CMake configure MSVC 2022 x64: PASS.
- Compile `cys_wxclient` (Game.exe): **FAIL**, chưa có `Game.exe`.
- Lỗi đầu tiên: `TDGameInterface.cpp:3: error C1083: Cannot open include file 'TDGameINTerFace.h'`.
- `TDGameInterface.h` không tồn tại trong source xuất bản dù `GMGameInterface.h` cần nó. `gameinterfacebase.h` cũng không có.
- Kiểm tra SDK: `fmod.h`, `fmod_vc.lib` và DirectX `d3dx9.lib` không có trong bản checkout.
- Logs thực: artifact `tlbb-client-build-logs` của run nói trên.
- **Không tạo header giả để build qua**, không tuyên bố có client chơi được.
- Chưa upload EXE công khai vì quyền phân phối code/tài nguyên kế thừa chưa được xác minh.

## Bước còn thiếu trước khi test 1 người

1. Phục hồi header gốc từ nguồn hợp lệ và SDK Windows x64, sau đó build Game.exe + DLL và kiểm bản chạy.
2. Dựng Linux server đầy đủ với các dependency đúng phiên bản, cài database riêng, tải data nếu quyền sử dụng cho phép.
3. Kiểm đăng nhập, tạo nhân vật, vào Đại Lý, di chuyển và thoát/đăng nhập lại.
4. Chỉ phát hành file tải khi bản chạy đã được kiểm tra và quyền phân phối hợp lệ.
