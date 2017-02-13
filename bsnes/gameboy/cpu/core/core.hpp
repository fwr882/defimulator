#include "registers.hpp"
void (CPU::*opcode_table[256])();
void (CPU::*opcode_table_cb[256])();
void initialize_opcode_table();

void op_xx(void);
void op_cb(void);

//8-bit load commands
template<unsigned x, unsigned y> void op_ld_r_r(void);
template<unsigned x> void op_ld_r_n(void);
template<unsigned x> void op_ld_r_hl(void);
template<unsigned x> void op_ld_hl_r(void);
void op_ld_hl_n(void);
template<unsigned x> void op_ld_a_rr(void);
void op_ld_a_nn(void);
template<unsigned x> void op_ld_rr_a(void);
void op_ld_nn_a(void);
void op_ld_a_ffn(void);
void op_ld_ffn_a(void);
void op_ld_a_ffc(void);
void op_ld_ffc_a(void);
void op_ldi_hl_a(void);
void op_ldi_a_hl(void);
void op_ldd_hl_a(void);
void op_ldd_a_hl(void);

//16-bit load commands
template<unsigned x> void op_ld_rr_nn(void);
void op_ld_nn_sp(void);
void op_ld_sp_hl(void);
template<unsigned x> void op_push_rr(void);
template<unsigned x> void op_pop_rr(void);

//8-bit arithmetic commands
void opi_add_a(uint8 x);
template<unsigned x> void op_add_a_r(void);
void op_add_a_n(void);
void op_add_a_hl(void);

void opi_adc_a(uint8 x);
template<unsigned x> void op_adc_a_r(void);
void op_adc_a_n(void);
void op_adc_a_hl(void);

void opi_sub_a(uint8 x);
template<unsigned x> void op_sub_a_r(void);
void op_sub_a_n(void);
void op_sub_a_hl(void);

void opi_sbc_a(uint8 x);
template<unsigned x> void op_sbc_a_r(void);
void op_sbc_a_n(void);
void op_sbc_a_hl(void);

void opi_and_a(uint8 x);
template<unsigned x> void op_and_a_r(void);
void op_and_a_n(void);
void op_and_a_hl(void);

void opi_xor_a(uint8 x);
template<unsigned x> void op_xor_a_r(void);
void op_xor_a_n(void);
void op_xor_a_hl(void);

void opi_or_a(uint8 x);
template<unsigned x> void op_or_a_r(void);
void op_or_a_n(void);
void op_or_a_hl(void);

void opi_cp_a(uint8 x);
template<unsigned x> void op_cp_a_r(void);
void op_cp_a_n(void);
void op_cp_a_hl(void);

template<unsigned x> void op_inc_r(void);
void op_inc_hl(void);
template<unsigned x> void op_dec_r(void);
void op_dec_hl(void);
void op_daa(void);
void op_cpl(void);

//16-bit arithmetic commands
template<unsigned x> void op_add_hl_rr(void);
template<unsigned x> void op_inc_rr(void);
template<unsigned x> void op_dec_rr(void);
void op_add_sp_n(void);
void op_ld_hl_sp_n(void);

//rotate/shift commands
void op_rlca(void);
void op_rla(void);
void op_rrca(void);
void op_rra(void);
template<unsigned x> void op_rlc_r(void);
void op_rlc_hl(void);
template<unsigned x> void op_rl_r(void);
void op_rl_hl(void);
template<unsigned x> void op_rrc_r(void);
void op_rrc_hl(void);
template<unsigned x> void op_rr_r(void);
void op_rr_hl(void);
template<unsigned x> void op_sla_r(void);
void op_sla_hl(void);
template<unsigned x> void op_swap_r(void);
void op_swap_hl(void);
template<unsigned x> void op_sra_r(void);
void op_sra_hl(void);
template<unsigned x> void op_srl_r(void);
void op_srl_hl(void);

//single-bit commands
template<unsigned b, unsigned x> void op_bit_n_r(void);
template<unsigned b> void op_bit_n_hl(void);
template<unsigned b, unsigned x> void op_set_n_r(void);
template<unsigned b> void op_set_n_hl(void);
template<unsigned b, unsigned x> void op_res_n_r(void);
template<unsigned b> void op_res_n_hl(void);

//control commands
void op_ccf(void);
void op_scf(void);
void op_nop(void);
void op_halt(void);
void op_stop(void);
void op_di(void);
void op_ei(void);

//jump commands
void op_jp_nn(void);
void op_jp_hl(void);
template<unsigned x, bool y> void op_jp_f_nn(void);
void op_jr_n(void);
template<unsigned x, bool y> void op_jr_f_n(void);
void op_call_nn(void);
template<unsigned x, bool y> void op_call_f_nn(void);
void op_ret(void);
template<unsigned x, bool y> void op_ret_f(void);
void op_reti(void);
template<unsigned n> void op_rst_n(void);

//disassembler.cpp
string disassemble(uint16 pc);
string disassemble_opcode(uint16 pc);
string disassemble_opcode_cb(uint16 pc);
