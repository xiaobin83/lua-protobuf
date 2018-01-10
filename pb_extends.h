// This file is written by Lanhai You, used for access proto types and fields from lua

#define T_PB_TYPE "pb.Type"
#define T_PB_FIELD "pb.Field"

static void Lpb_pushutype(lua_State *L, void *p, const char *type) {
    if (p == NULL) {
        lua_pushnil(L);
        return;
    }
    uintptr_t *u = lua_newuserdata(L, sizeof(void*));
    *u = (uintptr_t)p;
    lua_getfield(L, LUA_REGISTRYINDEX, type);
    lua_setmetatable(L, -2);
}

static void* Lpb_checkutype(lua_State *L, int idx, const char *type) {
    uintptr_t *u = checkudata(L, 1, type);
    return (void*)*u;
}

// types

static int Lpb_findtype(lua_State *L){
    pb_State *S = default_state(L);
    pb_Slice tname = lpb_checkslice(L, 1);
    pb_Type *t = pb_type(S, tname);
    Lpb_pushutype(L, t, T_PB_TYPE);
    return 1;
}

static int Lpb_exist(lua_State *L) {
    pb_State *S = default_state(L);
    pb_Slice tname = lpb_checkslice(L, 1);
    pb_Type *t = pb_type(S, tname);
    lua_pushboolean(L, t != NULL);
    return 1;
}

static int Ltype_name(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    lua_pushstring(L, t->name);
    return 1;
}

static int Ltype_basename(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    lua_pushstring(L, t->basename);
    return 1;
}

static int Ltype_isenum(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    lua_pushboolean(L, t->is_enum);
    return 1;
}

static int Ltype_ismap(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    lua_pushboolean(L, t->is_map);
    return 1;
}

static int Ltype_nfields(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    lua_pushinteger(L, t->field_names.size);
    return 1;
}

static int Ltype_getfield(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    int i = luaL_checkint(L, 2);
    if (i < 1 || i > t->field_names.size) {
        return 0;
    }
    pb_Entry *e = &(t->field_names.hash[i - 1]);
    pb_Field *f = (pb_Field*)e->value;
    Lpb_pushutype(L, f, T_PB_FIELD);
    return 1;
}

static int Ltype_findfield(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    pb_Slice s = lpb_toslice(L, -1);
    pb_Field *f = pb_field(t, s);
    Lpb_pushutype(L, f, T_PB_FIELD);
    return 1;
}

static int Ltype_to_enums(lua_State *L) {
    pb_Type *t = Lpb_checkutype(L, 1, T_PB_TYPE);
    pb_Entry *e;
    pb_Field *f;
    int i;
    if (!t->is_enum) {
        return 0;
    }
    lua_newtable(L);
    for (i = 0; i < t->field_names.size; ++i) {
        e = (pb_Entry*)(&t->field_names.hash[i]);
        f = (pb_Field*)e->value;
        if (f != NULL) {
            lua_pushstring(L, f->name);
            lua_pushinteger(L, f->u.enum_value);
            lua_rawset(L, -3);
        }
    }
    return 1;
}

// fields

static int Lfield_name(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    lua_pushstring(L, f->name);
    return 1;
}
static int Lfield_type(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    Lpb_pushutype(L, f->type, T_PB_TYPE);
    return 1;
}
static int Lfield_tag(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    lua_pushinteger(L, f->tag);
    return 1;
}
static int Lfield_value(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    lua_pushinteger(L, f->u.enum_value);
    return 1;
}
static int Lfield_isrepeated(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    lua_pushboolean(L, f->repeated);
    return 1;
}
static int Lfield_isrequired(lua_State *L) {
    pb_Field *f = Lpb_checkutype(L, 1, T_PB_FIELD);
    lua_pushboolean(L, f->required);
    return 1;
}

static void Lpb_registermetatable(lua_State *L, const char *name, luaL_Reg *libs) {
    if (luaL_newmetatable(L, name) == 0)
        return;
    luaL_setfuncs(L, libs, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_pushstring(L, name);
    lua_setfield(L, -2, "__cname");
    lua_pop(L, 1);
}

static void Lpb_registerextens(lua_State *L) {
    luaL_Reg libs[] = {
#define ENTRY(name) { #name, Lpb_##name }
        ENTRY(findtype),
        ENTRY(exist),
#undef  ENTRY
        { NULL, NULL },
    };
    luaL_Reg typelibs[] = {
#define ENTRY(name) {#name, Ltype_##name}
        ENTRY(name),
        ENTRY(basename),
        ENTRY(isenum),
        ENTRY(ismap),
        ENTRY(nfields),
        ENTRY(getfield),
        ENTRY(findfield),
        ENTRY(to_enums),
#undef  ENTRY
        { NULL, NULL },
    };
    luaL_Reg fieldlibs[] = {
#define ENTRY(name) {#name, Lfield_##name}
        ENTRY(name),
        ENTRY(type),
        ENTRY(tag),
        ENTRY(value),
        ENTRY(isrequired),
        ENTRY(isrepeated),
#undef  ENTRY
        { NULL, NULL },
    };

    luaL_setfuncs(L, libs, 0);

    Lpb_registermetatable(L, T_PB_TYPE, typelibs);
    Lpb_registermetatable(L, T_PB_FIELD, fieldlibs);
}
