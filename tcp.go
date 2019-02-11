package main

import (
	"flag"
	"fmt"
	"io"
	"net"
	"os"
)

func main() {
	ip := flag.String("ip", "10.70.1.6:15012", "EBS IP")
	packet := flag.String("packet", "002260001900000800203800000080000099000000000910150019013232303032323033", "What you want to send")
	tcpAddr, err := net.ResolveTCPAddr("tcp", *ip)
	if err != nil {
		panic(err)
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	// _, err := conn.Write([]byte("002260001900000800203800000080000099000000000910150019013232303032323033"))
	_, err = conn.Write([]byte(*packet))

	if err != nil {
		fmt.Printf("There's an error in writing to TCP connection socket: %s", err)
		os.Exit(1)
	}
	// result, err := ioutil.ReadAll(conn)

	// if err != nil {
	// 	fmt.Println("There is an error in TWO TITP response %v", err)
	// 	os.Exit(1)
	// }

	// fmt.Println(string(result))

	io.Copy(os.Stdout, conn)
	conn.Close()
}
