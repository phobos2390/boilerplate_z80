; file: main.asm

main:
  ld hl, hello_world_message
  call print_hl
  halt

print_hl:
  ld a,(hl)
  sub $0
  jp z, print_hl_end
  inc hl
  ld ($8000), a
  jp print_hl
print_hl_end:
  ret

hello_world_message:
.db "hello world",0