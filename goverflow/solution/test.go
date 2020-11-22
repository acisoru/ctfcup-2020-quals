package main

import (
	"bufio"
	"fmt"
	"os"
	"reflect"
	"unsafe"
)

var r = bufio.NewReader(os.Stdin)

func main() {
  stack_buf := [16]byte{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'}

  fmt.Println("[+] Hello, hacker! [+]")
  fmt.Println("[?] C4N y0u hAcK mE?? [?]")
  fmt.Print("[!] Send you payload: ")

  cSlice := make([]byte, 512)
  sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&cSlice))
  stack_buf_addr := uintptr(unsafe.Pointer(&(stack_buf[0])))
  sliceHeader.Data = stack_buf_addr

  _, _ = r.Read(cSlice)
}
