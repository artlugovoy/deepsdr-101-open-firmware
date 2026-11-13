/*
 * LOS MODOS QUE NO CABEN EN EL APM32 - 13/11/2026 (rama apm32).
 *
 * FT8, HFDL, WSPR, JTTY y STANAG/S4415 piden entre 38 y 73 kB del buffer
 * compartido y el APM32F407 tiene 128 kB de SRAM en total, asi que sus
 * fuentes no entran en `make apm32` (ver APM32_FUERA en reglas.mk). Lo que
 * el resto del firmware les llama se contesta aqui:
 *
 *   ..._activo(), ..._hay_hora(), contadores  -> 0: "no esta, no hay nada"
 *   ..._start()                               -> 0: "no arranca"
 *   ..._stop/_borra/_poll/_tick/_mete/_pon    -> no hacen nada
 *   textos                                    -> "" (nunca NULL)
 *   punteros de salida                        -> a cero / cadena vacia
 *
 * Generado a partir de los prototipos de las cabeceras de cada modo, que
 * se incluyen aqui: si una firma cambia, esto deja de compilar en vez de
 * enlazar algo distinto.
 *
 * Solo se compila en el build del APM32 (reglas.mk lo saca de los demas).
 */
#ifdef CHIP_APM32F407

#include <stdint.h>
#include <stdbool.h>

#include "ft8_lista.h"
#include "ft8_modo.h"
#include "hfdl_modo.h"
#include "jtty_modo.h"
#include "stanag_det.h"
#include "stanag_modo.h"
#include "wspr_modo.h"

/* --- ft8_lista.h -------------------------------------------- */

uint8_t ft8_lista_arrastra(int16_t *acum, int16_t dy, uint8_t alto, uint8_t *subidos)
{
    (void)acum; (void)dy; (void)alto;
    if (subidos) { *subidos = 0U; }
    return 0U;
}

uint8_t ft8_lista_escoge(const char *(*linea)(uint8_t), uint8_t guardadas, uint8_t solo_cq, uint8_t caben, uint8_t *subidos, uint8_t *idx)
{
    (void)linea; (void)guardadas; (void)solo_cq; (void)caben;
    if (subidos) { *subidos = 0U; }
    if (idx) { *idx = 0U; }
    return 0U;
}

uint8_t ft8_lista_es_cq(const char *linea)
{
    (void)linea;
    return 0U;
}

uint8_t ft8_lista_nuevos(const char *(*linea)(uint8_t), uint8_t cuantos, uint8_t solo_cq)
{
    (void)linea;
    (void)cuantos;
    (void)solo_cq;
    return 0U;
}

/* --- ft8_modo.h --------------------------------------------- */

uint8_t ft8_modo_activo(void)
{
    return 0U;
}

void ft8_modo_borra(void)
{
}

uint16_t ft8_modo_candidatos(void)
{
    return 0U;
}

void ft8_modo_come(const float *muestras, uint16_t n)
{
    (void)muestras;
    (void)n;
}

uint16_t ft8_modo_cortadas(void)
{
    return 0U;
}

void ft8_modo_cuadra(void)
{
}

void ft8_modo_db(int16_t *lo, int16_t *hi)
{
    if (lo) { *lo = 0; }
    if (hi) { *hi = 0; }
}

int16_t ft8_modo_dt_ms(void)
{
    return 0;
}

uint8_t ft8_modo_hay_hora(void)
{
    return 0U;
}

const char *ft8_modo_linea(uint8_t i)
{
    (void)i;
    return "";
}

uint32_t ft8_modo_metidas(void)
{
    return 0U;
}

uint16_t ft8_modo_ms(void)
{
    return 0U;
}

uint16_t ft8_modo_perdidos(void)
{
    return 0U;
}

uint8_t ft8_modo_segundo(void)
{
    return 0U;
}

void ft8_modo_start(float fs_hz)
{
    (void)fs_hz;
}

void ft8_modo_stop(void)
{
}

void ft8_modo_tick(void)
{
}

uint32_t ft8_modo_total(void)
{
    return 0U;
}

float ft8_modo_ventana_hz(void)
{
    return 0.0f;
}

/* --- hfdl_modo.h -------------------------------------------- */

uint8_t hfdl_modo_activo(void)
{
    return 0U;
}

uint32_t hfdl_modo_aviones(void)
{
    return 0U;
}

void hfdl_modo_borra(void)
{
}

uint32_t hfdl_modo_buenas(void)
{
    return 0U;
}

void hfdl_modo_datos(uint32_t *ud, uint32_t *pos)
{
    if (ud) { *ud = 0U; }
    if (pos) { *pos = 0U; }
}

void hfdl_modo_embudo(uint32_t *a1, uint32_t *a2, uint32_t *m1)
{
    if (a1) { *a1 = 0U; }
    if (a2) { *a2 = 0U; }
    if (m1) { *m1 = 0U; }
}

const char *hfdl_modo_estacion(void)
{
    return "";
}

uint8_t hfdl_modo_estado(void)
{
    return 0U;
}

uint8_t hfdl_modo_ficha(uint32_t i, char *out, uint8_t tope)
{
    (void)i;
    if (out && tope) { out[0] = '\0'; }
    return 0U;
}

uint8_t hfdl_modo_ident(uint32_t i, char *out, uint8_t tope)
{
    (void)i;
    if (out && tope) { out[0] = '\0'; }
    return 0U;
}

const char *hfdl_modo_linea(uint32_t i)
{
    (void)i;
    return "";
}

const char *hfdl_modo_linea_bytes(uint32_t i)
{
    (void)i;
    return "";
}

const char *hfdl_modo_linea_crc(void)
{
    return "";
}

uint32_t hfdl_modo_lineas(void)
{
    return 0U;
}

void hfdl_modo_mete(const float *i_in, const float *q_in, uint32_t n)
{
    (void)i_in;
    (void)q_in;
    (void)n;
}

void hfdl_modo_nivel_cambiado(void)
{
}

uint32_t hfdl_modo_no_cupo(void)
{
    return 0U;
}

uint32_t hfdl_modo_no_cupo_7(void)
{
    return 0U;
}

uint32_t hfdl_modo_pisada(void)
{
    return 0U;
}

void hfdl_modo_poll(void)
{
}

uint8_t hfdl_modo_pos(uint32_t i, int32_t *lat_e4, int32_t *lon_e4)
{
    (void)i;
    if (lat_e4) { *lat_e4 = 0; }
    if (lon_e4) { *lon_e4 = 0; }
    return 0U;
}

uint8_t hfdl_modo_senal(void)
{
    return 0U;
}

uint8_t hfdl_modo_start(void)
{
    return 0U;
}

void hfdl_modo_stop(void)
{
}

uint32_t hfdl_modo_total(void)
{
    return 0U;
}

/* --- jtty_modo.h -------------------------------------------- */

uint8_t jtty_modo_activo(void)
{
    return 0U;
}

uint32_t jtty_modo_atomos(void)
{
    return 0U;
}

void jtty_modo_borra(void)
{
}

const char *jtty_modo_estado_txt(void)
{
    return "";
}

const char *jtty_modo_linea(uint8_t i)
{
    (void)i;
    return "";
}

uint8_t jtty_modo_lineas(void)
{
    return 0U;
}

void jtty_modo_mete(const float *audio, uint16_t n)
{
    (void)audio;
    (void)n;
}

void jtty_modo_poll(void)
{
}

uint8_t jtty_modo_start(void)
{
    return 0U;
}

void jtty_modo_stop(void)
{
}

/* --- stanag_det.h ------------------------------------------- */

void stanag_det_fin(void)
{
}

uint8_t stanag_det_init(float *trabajo, uint32_t n_floats)
{
    (void)trabajo; (void)n_floats;
    return 0U;   /* no se puede: no hay detector */
}

void stanag_det_mete(const float *audio, uint32_t n)
{
    (void)audio;
    (void)n;
}

uint8_t stanag_det_paso(stanag_det_t *out)
{
    (void)out;
    return 0U;   /* nada detectado */
}

/* --- stanag_modo.h ------------------------------------------ */

uint8_t stanag_modo_4415(void)
{
    return 0U;
}

uint8_t stanag_modo_activo(void)
{
    return 0U;
}

void stanag_modo_borra(void)
{
}

uint8_t stanag_modo_demod(void)
{
    return 0U;
}

uint8_t stanag_modo_entre(void)
{
    return 0U;
}

void stanag_modo_entre_pon(uint8_t largo)
{
    (void)largo;
}

const char *stanag_modo_entre_txt(void)
{
    return "";
}

const char *stanag_modo_estado_txt(void)
{
    return "";
}

uint8_t stanag_modo_fmt(void)
{
    return 0U;
}

uint8_t stanag_modo_fmt_n(void)
{
    return 0U;
}

void stanag_modo_fmt_pon(uint8_t f)
{
    (void)f;
}

const char *stanag_modo_fmt_txt(void)
{
    return "";
}

uint8_t stanag_modo_forma(void)
{
    return 0U;
}

void stanag_modo_forma_pon(uint8_t f)
{
    (void)f;
}

const char *stanag_modo_forma_txt(uint8_t f)
{
    (void)f;
    return "";
}

uint32_t stanag_modo_latido(void)
{
    return 0U;
}

const char *stanag_modo_linea(uint8_t i)
{
    (void)i;
    return "";
}

uint8_t stanag_modo_lineas(void)
{
    return 0U;
}

void stanag_modo_llenado(uint16_t *hechos, uint16_t *hacen)
{
    if (hechos) { *hechos = 0U; }
    if (hacen) { *hacen = 0U; }
}

void stanag_modo_mete(const float *audio, uint16_t n)
{
    (void)audio;
    (void)n;
}

uint16_t stanag_modo_periodo(void)
{
    return 0U;
}

void stanag_modo_poll(void)
{
}

uint8_t stanag_modo_start(void)
{
    return 0U;
}

void stanag_modo_stop(void)
{
}

uint8_t stanag_modo_vel(void)
{
    return 0U;
}

uint8_t stanag_modo_vel_n(void)
{
    return 0U;
}

void stanag_modo_vel_pon(uint8_t v)
{
    (void)v;
}

const char *stanag_modo_vel_txt(void)
{
    return "";
}

/* --- wspr_modo.h -------------------------------------------- */

uint8_t wspr_modo_activo(void)
{
    return 0U;
}

void wspr_modo_borra(void)
{
}

uint16_t wspr_modo_buenas(void)
{
    return 0U;
}

uint8_t wspr_modo_capturando(void)
{
    return 0U;
}

uint16_t wspr_modo_espera_s(void)
{
    return 0U;
}

uint8_t wspr_modo_hay_hora(void)
{
    return 0U;
}

const char *wspr_modo_linea(uint32_t i)
{
    (void)i;
    return "";
}

uint32_t wspr_modo_lineas(void)
{
    return 0U;
}

void wspr_modo_mete(const float *audio, uint16_t n)
{
    (void)audio;
    (void)n;
}

void wspr_modo_poll(void)
{
}

uint8_t wspr_modo_por_ciento(void)
{
    return 0U;
}

uint8_t wspr_modo_q(void)
{
    return 0U;
}

uint8_t wspr_modo_start(void)
{
    return 0U;
}

void wspr_modo_stop(void)
{
}

#endif /* CHIP_APM32F407 */
