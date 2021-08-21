#include <assert.h>
#include <string.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"
#include "crypto/ecdsa.h"
#include "crypto/bignum.h"
#include "crypto/secp256k1.h"

/****************************** get_public_key33 ******************************/

STATIC mp_obj_t _ecc_get_public_key33(mp_obj_t arg){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    vstr_t vstr;
    if(bufinfo.len != 32){
        mp_raise_ValueError(MP_ERROR_TEXT("Private key should be 32 bytes long"));
        return mp_const_none;
    }
    vstr_init_len(&vstr, 33);
    ecdsa_get_public_key33(&secp256k1, bufinfo.buf, (byte*)vstr.buf);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(_ecc_get_public_key33_obj, _ecc_get_public_key33);

/****************************** get_public_key65 ******************************/

STATIC mp_obj_t _ecc_get_public_key65(mp_obj_t arg){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    vstr_t vstr;
    if(bufinfo.len != 32){
        mp_raise_ValueError(MP_ERROR_TEXT("Private key should be 32 bytes long"));
        return mp_const_none;
    }
    vstr_init_len(&vstr, 65);
    ecdsa_get_public_key65(&secp256k1, bufinfo.buf, (byte*)vstr.buf);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(_ecc_get_public_key65_obj, _ecc_get_public_key65);

/****************************** point_add ******************************/

STATIC mp_obj_t _ecc_point_add(mp_obj_t point_a, mp_obj_t point_b){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(point_a, &bufinfo, MP_BUFFER_READ);
    curve_point pa;
    ecdsa_read_pubkey(&secp256k1, bufinfo.buf, &pa);

    mp_get_buffer_raise(point_b, &bufinfo, MP_BUFFER_READ);
    curve_point pb;
    ecdsa_read_pubkey(&secp256k1, bufinfo.buf, &pb);

    point_add(&secp256k1, &pa, &pb);

    vstr_t vstr;
    vstr_init_len(&vstr, 65);
    ((byte*)vstr.buf)[0] = 0x04;
    bn_write_be(&pb.x, (byte*)vstr.buf+1);
    bn_write_be(&pb.y, (byte*)vstr.buf+33);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(_ecc_point_add_obj, _ecc_point_add);

/****************************** point_multiply ******************************/

STATIC mp_obj_t _ecc_point_multiply(mp_obj_t scalar, mp_obj_t point){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(scalar, &bufinfo, MP_BUFFER_READ);
    bignum256 sc;
    bn_read_be(bufinfo.buf, &sc);

    mp_get_buffer_raise(point, &bufinfo, MP_BUFFER_READ);
    curve_point p;
    ecdsa_read_pubkey(&secp256k1, bufinfo.buf, &p);

    curve_point res;
    point_multiply(&secp256k1, &sc, &p, &res);

    vstr_t vstr;
    vstr_init_len(&vstr, 65);
    ((byte*)vstr.buf)[0] = 0x04;
    bn_write_be(&res.x, (byte*)vstr.buf+1);
    bn_write_be(&res.y, (byte*)vstr.buf+33);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(_ecc_point_multiply_obj, _ecc_point_multiply);

/****************************** validate_pubkey ******************************/

STATIC mp_obj_t _ecc_validate_pubkey(mp_obj_t point){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(point, &bufinfo, MP_BUFFER_READ);
    curve_point p;
    ecdsa_read_pubkey(&secp256k1, bufinfo.buf, &p);
    int i = ecdsa_validate_pubkey(&secp256k1, &p);
    return mp_obj_new_bool(i);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(_ecc_validate_pubkey_obj, _ecc_validate_pubkey);

/****************************** uncompress_pubkey ******************************/

STATIC mp_obj_t _ecc_uncompress_pubkey(mp_obj_t point){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(point, &bufinfo, MP_BUFFER_READ);
    curve_point p;
    ecdsa_read_pubkey(&secp256k1, bufinfo.buf, &p);
    vstr_t vstr;
    vstr_init_len(&vstr, 65);
    ((byte*)vstr.buf)[0] = 0x04;
    bn_write_be(&p.x, (byte*)vstr.buf+1);
    bn_write_be(&p.y, (byte*)vstr.buf+33);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(_ecc_uncompress_pubkey_obj, _ecc_uncompress_pubkey);

/****************************** MODULE ******************************/

STATIC const mp_rom_map_elem_t _ecc_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR__ecc) },
    { MP_ROM_QSTR(MP_QSTR_get_public_key33), MP_ROM_PTR(&_ecc_get_public_key33_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_public_key65), MP_ROM_PTR(&_ecc_get_public_key65_obj) },
    { MP_ROM_QSTR(MP_QSTR_point_add), MP_ROM_PTR(&_ecc_point_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_point_multiply), MP_ROM_PTR(&_ecc_point_multiply_obj) },
    { MP_ROM_QSTR(MP_QSTR_validate_pubkey), MP_ROM_PTR(&_ecc_validate_pubkey_obj) },
    { MP_ROM_QSTR(MP_QSTR_uncompress_pubkey), MP_ROM_PTR(&_ecc_uncompress_pubkey_obj) },
};
STATIC MP_DEFINE_CONST_DICT(_ecc_module_globals, _ecc_module_globals_table);

// Define module object.
const mp_obj_module_t _ecc_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&_ecc_module_globals,
};

// Register the module to make it available in Python
MP_REGISTER_MODULE(MP_QSTR__ecc, _ecc_user_cmodule, MODULE_ECC_ENABLED);
