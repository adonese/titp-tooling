package main

import (
	"bytes"
	"fmt"
	"github.com/ideazxy/iso8583"
	"io"
	"net"
	"os"
	"time"
)

type ISOSignIn struct {
	Bit3 *iso8583.Numeric `field:"3" length:"6"`
	Bit11 *iso8583.Numeric `field:"11" length:"6"`
	Bit12 *iso8583.Numeric `field:"12" length:"6"`
	Bit13 *iso8583.Numeric `field:"13" length:"4"`
	Bit41 *iso8583.Alphanumeric `field:"41" length:"8"`
}

func main() {
	//testIso()
	//data := []byte("002260001900000800203800000080000099000000000414150008023232323233333333")
	//tcpClientNew(data)
	d := testIso()
	fmt.Printf("% x\n", d)
	tcpClientNew(d)
}

func testIso() []byte{
	data := ISOSignIn{
		Bit3:  iso8583.NewNumeric("1"),
		Bit11: iso8583.NewNumeric("4"),
		Bit12: iso8583.NewNumeric("141500"),
		Bit13: iso8583.NewNumeric("0211"),
		Bit41: iso8583.NewAlphanumeric("19000019"),
	}
	msg := iso8583.NewMessage("0800", data)
	msg.MtiEncode = iso8583.BCD
	b, err := msg.Bytes()
	if err != nil {
		fmt.Println(err.Error())
	}
	return b
}

func tcpClientNew(b []byte) {
	tcpAddr, err := net.ResolveTCPAddr("tcp", "10.70.1.6:15012")
	if err != nil {
		println("ResolveTCPAddr failed:", err.Error())
		os.Exit(1)
	}
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		println("Dial failed:", err.Error())
		os.Exit(1)
	}
	timeoutDuration := 50 * time.Second

	_, err = conn.Write(b)
	if err != nil {
		println("Write to server failed:", err.Error())
		os.Exit(1)
	}
	defer conn.Close()

	conn.SetReadDeadline(time.Now().Add(timeoutDuration))

	//bufReader := bufio.NewReader(conn)
	//recvBuf := make([]byte, 1024)
	//n, err := bufReader.Read(recvBuf)
	//for err == nil {
	//	println("Recv data from server:", string(recvBuf[:n]))
	//	n, err = bufReader.Read(recvBuf)
	//}
	//if err != io.EOF {
	//	println("recv from server failed, err:", err.Error())
	//	fmt.Println(reflect.TypeOf(err))
	//
	//}else{
	//	fmt.Printf("Unexpected error: %s\n", err.Error())
	//	fmt.Println(reflect.TypeOf(err))
	//}
	var buf bytes.Buffer

	io.Copy(&buf, conn)
	fmt.Println("Total length: \n", buf.Len())
	fmt.Printf("Received buffer is: %x", buf.Bytes())

}