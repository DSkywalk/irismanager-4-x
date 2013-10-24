/* 
    (c) 2011-2013 Hermes/Estwald <www.elotrolado.net>
    IrisManager (HMANAGER port) (c) 2011 D_Skywalk <http://david.dantoine.org>

    HMANAGER4 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HMANAGER4 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HMANAGER4.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "ps3_discless.h"
#include "utils.h"

#include "ps3_storage_bin.h"

u64 lv2peek(u64 addr);
u64 lv2poke(u64 addr, u64 value);
extern u64 syscall_base;

static u64 syscall_40(u64 cmd, u64 arg)
{
    lv2syscall2(40, cmd, arg);

    return_to_user_prog(u64);
    
}

u8 in_51[8]= {
    0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 out_51[]= {
    0x00, 0x20, 0x0e, 0x01, 0x01, 0x01, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

u8 in_bb[8]= {
    0xbb, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
};

u8 out_bb[]= {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 in_a4[8]= {
    0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0
};

u8 out_a4[]= {
    0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
};

u8 in_ad[8]= {
    0xad, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 out_ad[]= {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

u8 in_43[8]= {
    0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 out_43[]= {
    0x00, 0x12, 0x01, 0x01, 0x00, 0x14, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xaa, 0x00,
    0x00, 0x00
};

u8 in_46[8]= {
    0x46, 0x01, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00
};

u8 out_46[]= {
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 in_46b[8]= {
    0x46, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00
};

u8 out_46b[]= {
    0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x03, 0x00, 0x01, 0x05, 0x07, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0d, 0x04, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x08, 0x03, 0x14,
    0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
    0x46, 0x46, 0x46, 0x46, 0xff, 0x00, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 in_46c[8]= {
    0x4a, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
};

u8 out_46c[]= {
    0x00, 0x06, 0x04, 0x56, 0x00, 0x02, 0x00, 0x00
};

void send_async_data_table(void)
{
    u32 pos = 0x7DF000;

    int n = 18 * 4, m;
    u32 data[4096];

    data[0]= pos + n;
    data[1]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_51, 8);
    n += 8;
    m = sizeof(out_51);
    memcpy((void *) &data[n>>2], (void *) out_51, m);
    n= ((n + m + 7) & ~7);

    data[2]= pos + n;
    data[3]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_bb, 8);
    n += 8;
    m = sizeof(out_bb);
    memcpy((void *) &data[n>>2], (void *) out_bb, m);
    n= ((n + m + 7) & ~7);

    data[4]= pos + n;
    data[5]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_a4, 8);
    n += 8;
    m = sizeof(out_a4);
    memcpy((void *) &data[n>>2], (void *) out_a4, m);
    n= ((n + m + 7) & ~7);

    data[6]= pos + n;
    data[7]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_ad, 8);
    n += 8;
    m = sizeof(out_ad);
    memcpy((void *) &data[n>>2], (void *) out_ad, m);
    n= ((n + m + 7) & ~7);

    data[8]= pos + n;
    data[9]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_43, 8);
    n += 8;
    m = sizeof(out_43);
    memcpy((void *) &data[n>>2], (void *) out_43, m);
    n= ((n + m + 7) & ~7);

    data[10]= pos + n;
    data[11]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_46, 8);
    n += 8;
    m = sizeof(out_46);
    memcpy((void *) &data[n>>2], (void *) out_46, m);
    n= ((n + m + 7) & ~7);

    data[12]= pos + n;
    data[13]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_46b, 8);
    n += 8;
    m = sizeof(out_46b);
    memcpy((void *) &data[n>>2], (void *) out_46b, m);
    n= ((n + m + 7) & ~7);

    data[14]= pos + n;
    data[15]= pos + n + 8;
    memcpy((void *) &data[n>>2], (void *) in_46c, 8);
    n += 8;
    m = sizeof(out_51);
    memcpy((void *) &data[n>>2], (void *) out_46c, m);
    n= ((n + m + 7) & ~7);

    data[16]=data[17]=0;

    sys8_memcpy(0x8000000000000000ULL + (u64) pos, (u64) data, (u64) n);

    syscall_40(2, 0x8000000000000000ULL + (u64) pos);
}

static u64 PAYLOAD_BASE = 0ULL;

static void write_htab(void)
{
    u64 cont = 0;
    lv1_reg regs_i, regs_o;
    u32 val;

    while(cont < 0x80) {
        val = (cont << 7);

        regs_i.reg3 = 0;
        regs_i.reg4 = (cont << 3ULL);
        regs_i.reg5 = lv2peek(0x800000000f000000ULL | ((u64) val));
        regs_i.reg6 = lv2peek(0x800000000f000008ULL | ((u64) val));
        regs_i.reg6 = (regs_i.reg6  & 0xff0000ULL) | 0x190ULL;
        regs_i.reg11= 1;

        sys8_lv1_syscall(&regs_i, &regs_o);

        cont++;

    }
}

void load_ps3_discless_payload()
{

    u64 *addr= (u64 *) memalign(8, ps3_storage_bin_size + 31);

    if(!addr) {
        DrawDialogOK("Shit! full memory");
        exit(0);
    }

    if(!syscall_base) {
        DrawDialogOK("syscall_base is empty!");
        return;
    }
    
    if(lv2peek(0x80000000000004E8ULL)) goto skip_the_load;

    write_htab();

    PAYLOAD_BASE = 0x80000000007FE000ULL;

    memcpy((char *) addr, (char *) ps3_storage_bin, ps3_storage_bin_size);

    addr[1] = syscall_base;
    addr[2] += PAYLOAD_BASE; // sys 40
    addr[3] = lv2peek(syscall_base + (u64) (40 * 8));
    addr[4] += PAYLOAD_BASE;
    addr[5] = lv2peek(syscall_base + (u64) (130 * 8));
    //addr[6] += PAYLOAD_BASE;
    //addr[7] = lv2peek(syscall_base + (u64) (600 * 8));
    addr[8] += PAYLOAD_BASE;
    addr[9] = lv2peek(syscall_base + (u64) (864 * 8));
    addr[10] += PAYLOAD_BASE;
    addr[11] = lv2peek(syscall_base + (u64) (619 * 8));
    addr[12] += PAYLOAD_BASE;
    addr[13] = lv2peek(syscall_base + (u64) (837 * 8));
    addr[14] += PAYLOAD_BASE;
    addr[15] = lv2peek(syscall_base + (u64) (609 * 8));

    int n;

    for(n=0;n<200;n++) {

    lv2poke(0x80000000000004E8ULL, PAYLOAD_BASE);

    sys8_memcpyinstr(PAYLOAD_BASE, (u64) addr, (u64) ((ps3_storage_bin_size + 7) & ~7));

    lv2poke(syscall_base + (u64) (40 * 8), PAYLOAD_BASE + 0x10ULL);
    lv2poke(syscall_base + (u64) (130 * 8), PAYLOAD_BASE + 0x20ULL);
    //lv2poke(syscall_base + (u64) (600 * 8), PAYLOAD_BASE + 0x30ULL);
    lv2poke(syscall_base + (u64) (864 * 8), PAYLOAD_BASE + 0x40ULL);
    lv2poke(syscall_base + (u64) (619 * 8), PAYLOAD_BASE + 0x50ULL);
    lv2poke(syscall_base + (u64) (837 * 8), PAYLOAD_BASE + 0x60ULL);
    lv2poke(syscall_base + (u64) (609 * 8), PAYLOAD_BASE + 0x70ULL);

    usleep(10000);
    }

    sleep(1);
skip_the_load:
    free(addr);

    send_async_data_table();
}


