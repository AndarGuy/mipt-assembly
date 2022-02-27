| **Name**  | **Symbol** | **Bit** | **Content**                                                      |
| --------- | ---------- | ------- | ---------------------------------------------------------------- |
| Carry     | CF         | 0       | Previous instruction had a carry                                 |
| Parity    | PF         | 2       | Last byte has even number of 1s                                  |
| Adjust    | AF         | 4       | BCD operations                                                   |
| Zero      | ZF         | 6       | Previous instruction resulted a zero                             |
| Sign      | SF         | 8       | Previous instruction resulted in most significant bit equal to 1 |
| Direction | DF         | 10      | Direction of string operations (increment or decrement)          |
| Overflow  | OF         | 11      | Previous instruction resulted in overflow                        |
