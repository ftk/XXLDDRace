#include <engine/shared/config.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "loltext.h"

CLolPlasma::CLolPlasma(CGameWorld *pGameWorld, CEntity *pParent, vec2 Pos, vec2 Vel, int Lifespan)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_LASER)
{
	m_LocalPos = vec2(0.0f, 0.0f);
	m_StartOff = Pos;
	CEntity::m_Pos = (pParent?pParent->m_Pos:vec2(0.0f,0.0f)) + m_StartOff;
	m_Vel = Vel;
	m_Life = Lifespan;
	m_StartTick = Server()->Tick();
	m_pParent = pParent;
	GameWorld()->InsertEntity(this);
}

void CLolPlasma::Reset()
{
	GameWorld()->DestroyEntity(this);
}

void CLolPlasma::Tick()
{
	if (m_Life < 0)
	{
		Reset();
		return;
	}
	m_Life--;

	CEntity::m_Pos = (m_pParent?m_pParent->m_Pos:vec2(0.0f,0.0f)) + m_StartOff + (m_LocalPos += m_Vel);
}

void CLolPlasma::Snap(int SnappingClient)
{
	if (NetworkClipped(SnappingClient))
		return;


	CNetObj_Laser *pObj = static_cast<CNetObj_Laser*>
	            (Server()->SnapNewItem(NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));

	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_Pos.x;
	pObj->m_FromY = (int)m_Pos.y;
	pObj->m_StartTick = m_StartTick;

}


vec2 CLoltext::TextSize(const char *pText)
{
	int Count = 0;
	char c;
	while((c = str_utf8_decode(&pText)))
	{
		if(GetRepr(c) == -1ULL)
			continue;
		++Count;
	}//no there ain't linebreaks
	return vec2(Count*g_Config.m_SvLoltextHspace*4.0f, g_Config.m_SvLoltextVspace);
}

void CLoltext::Create(CGameWorld *pGameWorld, CEntity *pParent, vec2 Pos, vec2 Vel, int Lifespan, const char *pText, bool Center, bool Follow)
{
	int c;
	vec2 CurPos = Pos;
	if (Center)
		CurPos -= TextSize(pText)*0.5f;

	if (pParent && !Follow)
	{
		CurPos += pParent->m_Pos;
		pParent = 0;
	}

	while((c = str_utf8_decode(&pText)))
	{
		unsigned long long Repr = GetRepr(c);
                if(Repr == -1ULL)
			continue;
		for(int y = 0; y < 8; ++y)
			for(int x = 0; x < 8/*XXX*/; ++x)
				if(((Repr >> (56 - y*8)) >> x) & 1)
					new CLolPlasma(pGameWorld, pParent, CurPos + vec2(x*g_Config.m_SvLoltextHspace, y*g_Config.m_SvLoltextVspace), Vel, Lifespan);
		CurPos.x += 9*g_Config.m_SvLoltextHspace;
	}
}

unsigned long long CLoltext::GetRepr(int c)
{
	if(c < 0)
		return -1ULL;
	if(c < 128)
		return s_aChars[c];
	switch(c)
	{
        case   164: return 0x00633e63633e6300ULL; /* ¤ */
        case   167: return 0x7c063c66663c603eULL; /* § */
        case   173: return 0x0000000018000000ULL; /* ­ */
        case   176: return 0x1c36361c00000000ULL; /* ° */
        case   183: return 0x0000001818000000ULL; /* · */
        case  1025: return 0x367f461e06467f00ULL; /* Ё */
        case  1028: return 0x3c66031f03663c00ULL; /* Є */
        case  1031: return 0x121e0c0c0c0c1e00ULL; /* Ї */
        case  1038: return 0x146b637e60633e00ULL; /* Ў */
        case  1040: return 0x7c6663637f636300ULL; /* А */
        case  1041: return 0x7f66063e66663f00ULL; /* Б */
        case  1042: return 0x3f66663e66663f00ULL; /* В */
        case  1043: return 0x7f66060606060f00ULL; /* Г */
        case  1044: return 0x786c66666666ffc3ULL; /* Д */
        case  1045: return 0x7f46161e16467f00ULL; /* Е */
        case  1046: return 0x6b6b3e1c3e6b6b00ULL; /* Ж */
        case  1047: return 0x3e63603c60633e00ULL; /* З */
        case  1048: return 0x6363737b6f676300ULL; /* И */
        case  1049: return 0x1c63737b6f676300ULL; /* Й */
        case  1050: return 0x6766361e36666700ULL; /* К */
        case  1051: return 0x786c666666666300ULL; /* Л */
        case  1052: return 0x63777f7f6b636300ULL; /* М */
        case  1053: return 0x6363637f63636300ULL; /* Н */
        case  1054: return 0x3e63636363633e00ULL; /* О */
        case  1055: return 0x7f63636363636300ULL; /* П */
        case  1056: return 0x3f6666663e060f00ULL; /* Р */
        case  1057: return 0x3e63030303633e00ULL; /* С */
        case  1058: return 0x7e5a181818183c00ULL; /* Т */
        case  1059: return 0x6363637e60633e00ULL; /* У */
        case  1060: return 0x3e6b6b6b3e081c00ULL; /* Ф */
        case  1061: return 0x6363361c36636300ULL; /* Х */
        case  1062: return 0x3333333333337f60ULL; /* Ц */
        case  1063: return 0x6363637e60606000ULL; /* Ч */
        case  1064: return 0x6b6b6b6b6b6b7f00ULL; /* Ш */
        case  1065: return 0x6b6b6b6b6b6bffc0ULL; /* Щ */
        case  1066: return 0x0f0f0d3c6c6c3c00ULL; /* Ъ */
        case  1067: return 0x6363636f7b7b6f00ULL; /* Ы */
        case  1068: return 0x0f06063e66663e00ULL; /* Ь */
        case  1069: return 0x1e31607c60311e00ULL; /* Э */
        case  1070: return 0x3b6b6b6f6b6b3b00ULL; /* Ю */
        case  1071: return 0x7e6363637e666300ULL; /* Я */
        case  1072: return 0x00001e303e336e00ULL; /* а */
        case  1073: return 0x603e033f63633e00ULL; /* б */
        case  1074: return 0x00003f663e663f00ULL; /* в */
        case  1075: return 0x00007f6606060f00ULL; /* г */
        case  1076: return 0x00003c3636367f63ULL; /* д */
        case  1077: return 0x00003e637f033e00ULL; /* е */
        case  1078: return 0x00006b3e1c3e6b00ULL; /* ж */
        case  1079: return 0x00003e6338633e00ULL; /* з */
        case  1080: return 0x000063737b6f6700ULL; /* и */
        case  1081: return 0x001c63737b6f6700ULL; /* й */
        case  1082: return 0x000067361e366700ULL; /* к */
        case  1083: return 0x00007c6666666300ULL; /* л */
        case  1084: return 0x000063777f6b6300ULL; /* м */
        case  1085: return 0x000063637f636300ULL; /* н */
        case  1086: return 0x00003e6363633e00ULL; /* о */
        case  1087: return 0x00007f6363636300ULL; /* п */
        case  1088: return 0x00003f66663e060fULL; /* р */
        case  1089: return 0x00003e6303633e00ULL; /* с */
        case  1090: return 0x00007e5a18183c00ULL; /* т */
        case  1091: return 0x00006363637e603eULL; /* у */
        case  1092: return 0x00003e6b6b3e081cULL; /* ф */
        case  1093: return 0x000063361c366300ULL; /* х */
        case  1094: return 0x0000333333337f60ULL; /* ц */
        case  1095: return 0x000063637e606000ULL; /* ч */
        case  1096: return 0x00006b6b6b6b7f00ULL; /* ш */
        case  1097: return 0x00006b6b6b6bffc0ULL; /* щ */
        case  1098: return 0x00000f0d3c6c3c00ULL; /* ъ */
        case  1099: return 0x000063636f7b6f00ULL; /* ы */
        case  1100: return 0x00000f063e663f00ULL; /* ь */
        case  1101: return 0x00003e6378633e00ULL; /* э */
        case  1102: return 0x00003b6b6f6b3b00ULL; /* ю */
        case  1103: return 0x00007e637e666300ULL; /* я */
        case  1105: return 0x36003e637f033e00ULL; /* ё */
        case  1108: return 0x00007cc61ec67c00ULL; /* є */
        case  1111: return 0x33000e0c0c0c1e00ULL; /* ї */
        case  1118: return 0x221c6363637e603eULL; /* ў */
        case  8470: return 0xf1b3f73ffb333300ULL; /* № */
        case  8730: return 0x703030363c383000ULL; /* √ */
        case  9472: return 0x000000ff00000000ULL; /* ─ */
        case  9474: return 0x1818181818181818ULL; /* │ */
        case  9484: return 0x000000f818181818ULL; /* ┌ */
        case  9488: return 0x0000001f18181818ULL; /* ┐ */
        case  9492: return 0x181818f800000000ULL; /* └ */
        case  9496: return 0x1818181f00000000ULL; /* ┘ */
        case  9500: return 0x181818f818181818ULL; /* ├ */
        case  9508: return 0x1818181f18181818ULL; /* ┤ */
        case  9516: return 0x000000ff18181818ULL; /* ┬ */
        case  9524: return 0x181818ff00000000ULL; /* ┴ */
        case  9532: return 0x181818ff18181818ULL; /* ┼ */
        case  9552: return 0x00ff00ff00000000ULL; /* ═ */
        case  9553: return 0x6c6c6c6c6c6c6c6cULL; /* ║ */
        case  9554: return 0x00f818f818181818ULL; /* ╒ */
        case  9555: return 0x000000fc6c6c6c6cULL; /* ╓ */
        case  9556: return 0x00fc0cec6c6c6c6cULL; /* ╔ */
        case  9557: return 0x001f181f18181818ULL; /* ╕ */
        case  9558: return 0x0000007f6c6c6c6cULL; /* ╖ */
        case  9559: return 0x007f606f6c6c6c6cULL; /* ╗ */
        case  9560: return 0x18f818f800000000ULL; /* ╘ */
        case  9561: return 0x6c6c6cfc00000000ULL; /* ╙ */
        case  9562: return 0x6cec0cfc00000000ULL; /* ╚ */
        case  9563: return 0x181f181f00000000ULL; /* ╛ */
        case  9564: return 0x6c6c6c7f00000000ULL; /* ╜ */
        case  9565: return 0x6c6f607f00000000ULL; /* ╝ */
        case  9566: return 0x18f818f818181818ULL; /* ╞ */
        case  9567: return 0x6c6c6cec6c6c6c6cULL; /* ╟ */
        case  9568: return 0x6cec0cec6c6c6c6cULL; /* ╠ */
        case  9569: return 0x181f181f18181818ULL; /* ╡ */
        case  9570: return 0x6c6c6c6f6c6c6c6cULL; /* ╢ */
        case  9571: return 0x6c6f606f6c6c6c6cULL; /* ╣ */
        case  9572: return 0x00ff00ff18181818ULL; /* ╤ */
        case  9573: return 0x000000ff6c6c6c6cULL; /* ╥ */
        case  9574: return 0x00ff00ef6c6c6c6cULL; /* ╦ */
        case  9575: return 0x18ff00ff00000000ULL; /* ╧ */
        case  9576: return 0x6c6c6cff00000000ULL; /* ╨ */
        case  9577: return 0x6cef00ff00000000ULL; /* ╩ */
        case  9578: return 0x18ff18ff18181818ULL; /* ╪ */
        case  9579: return 0x6c6c6cff6c6c6c6cULL; /* ╫ */
        case  9580: return 0x6cef00ef6c6c6c6cULL; /* ╬ */
        case  9600: return 0xffffff0000000000ULL; /* ▀ */
        case  9604: return 0x000000ffffffffffULL; /* ▄ */
        case  9608: return 0xffffffffffffffffULL; /* █ */
        case  9612: return 0x0f0f0f0f0f0f0f0fULL; /* ▌ */
        case  9616: return 0xf0f0f0f0f0f0f0f0ULL; /* ▐ */
        case  9617: return 0x8822882288228822ULL; /* ░ */
        case  9618: return 0xaa55aa55aa55aa55ULL; /* ▒ */
	case  9619: return 0xbbeebbeebbeebbeeULL; /* ▓ */
	case  9632: return 0x00003c3c3c3c0000ULL; /* ■ */
	}
	return -1ULL;
}


unsigned long long CLoltext::s_aChars[128] = {
        0x00180c060c18001eULL, //        0
	0x00060c180c06001eULL, //        1 
        0x0070d8d818181818ULL, //        2 
        0x181818181b1b0e00ULL, //        3 
        0x001818007e001818ULL, //        4 
        0x0f06366e66666730ULL, //        5 
        0x107f660606060f00ULL, //        6 
        0x3e63061c30633e00ULL, //        7 
        0x3c18181818183c00ULL, //        8 
        0x7830303033331e00ULL, //        9
        0x0000000000000000ULL, //       10
        0x3333337fb3b37300ULL, //       11 
        0x0f063e6666666700ULL, //       12 
        0x0000000000000000ULL, //       13
        0x6363636363637f08ULL, //       14 
        0x407f060606060f00ULL, //       15 
        0x006e3b006e3b0000ULL, //       16 
        0x7e81bd8585bd817eULL, //       17 
        0x0c1208041e000000ULL, //       18 
        0x7e819da59da5817eULL, //       19 
        0x3c461f060f463c00ULL, //       20 
        0x060f06366e666730ULL, //       21 
        0x20107f4606060f00ULL, //       22 
        0x00007e033e603f00ULL, //       23 
        0x18001c1818183c00ULL, //       24 
        0x600060606066663cULL, //       25 
        0x00003c3676b67300ULL, //       26 
        0x000033337fb37300ULL, //       27 
        0x060f06366e666600ULL, //       28 
        0x100867361e366700ULL, //       29 
        0x0000636363637f08ULL, //       30 
        0x00407f0606060f00ULL, //       31 
        0x0000000000000000ULL, //       32
        0x183c3c1818001800ULL, //       33 !
        0x6666240000000000ULL, //       34 "
        0x36367f367f363600ULL, //       35 #
        0x187c063c603e1800ULL, //       36 $
        0x006333180c666300ULL, //       37 %
        0x1c361c6e3b336e00ULL, //       38 &
        0x18180c0000000000ULL, //       39 '
        0x30180c0c0c183000ULL, //       40 (
        0x0c18303030180c00ULL, //       41 )
        0x00663cff3c660000ULL, //       42 *
        0x0018187e18180000ULL, //       43 +
        0x000000000018180cULL, //       44 ,
        0x0000007e00000000ULL, //       45 -
        0x0000000000181800ULL, //       46 .
        0x6030180c06030100ULL, //       47 /
        0x3e63736b67633e00ULL, //       48 0
        0x181c181818187e00ULL, //       49 1
        0x3e6360380e637f00ULL, //       50 2
        0x3e63603c60633e00ULL, //       51 3
        0x383c36337f307800ULL, //       52 4
        0x7f03033f60633e00ULL, //       53 5
        0x1c06033f63633e00ULL, //       54 6
        0x7f6330180c0c0c00ULL, //       55 7
        0x3e63633e63633e00ULL, //       56 8
        0x3e63637e60301e00ULL, //       57 9
        0x0018180000181800ULL, //       58 :
        0x001818000018180cULL, //       59 ;
        0x6030180c18306000ULL, //       60 <
        0x00007e00007e0000ULL, //       61 =
        0x060c1830180c0600ULL, //       62 >
        0x3e63301818001800ULL, //       63 ?
        0x3e637b7b3b031e00ULL, //       64 @
        0x1c36637f63636300ULL, //       65 A
        0x3f66663e66663f00ULL, //       66 B
        0x3c66030303663c00ULL, //       67 C
        0x1f36666666361f00ULL, //       68 D
        0x7f46161e16467f00ULL, //       69 E
        0x7f46161e16060f00ULL, //       70 F
        0x3c66030373665c00ULL, //       71 G
        0x6363637f63636300ULL, //       72 H
        0x3c18181818183c00ULL, //       73 I
        0x7830303033331e00ULL, //       74 J
        0x6766361e36666700ULL, //       75 K
        0x0f06060646667f00ULL, //       76 L
        0x63777f7f6b636300ULL, //       77 M
        0x63676f7b73636300ULL, //       78 N
        0x3e63636363633e00ULL, //       79 O
        0x3f66663e06060f00ULL, //       80 P
        0x3e63636363733e70ULL, //       81 Q
        0x3f66663e36666700ULL, //       82 R
        0x3e63061c30633e00ULL, //       83 S
        0x7e7e5a1818183c00ULL, //       84 T
        0x6363636363633e00ULL, //       85 U
        0x6363636363361c00ULL, //       86 V
        0x6363636b6b7f3600ULL, //       87 W
        0x6363361c36636300ULL, //       88 X
        0x6666663c18183c00ULL, //       89 Y
        0x7f6331184c667f00ULL, //       90 Z
        0x3c0c0c0c0c0c3c00ULL, //       91 [
        0x03060c1830604000ULL, //       92 '\\'
        0x3c30303030303c00ULL, //       93 ]
        0x081c366300000000ULL, //       94 ^
        0x00000000000000ffULL, //       95 _
        0x0c18300000000000ULL, //       96 `
        0x00001e303e336e00ULL, //       97 a
        0x07063e6666663b00ULL, //       98 b
        0x00003e6303633e00ULL, //       99 c
        0x38303e3333336e00ULL, //      100 d
        0x00003e637f033e00ULL, //      101 e
        0x3c66061f06060f00ULL, //      102 f
        0x00006e33333e301fULL, //      103 g
        0x0706366e66666700ULL, //      104 h
        0x18001c1818183c00ULL, //      105 i
        0x600060606066663cULL, //      106 j
        0x070666361e366700ULL, //      107 k
        0x1c18181818183c00ULL, //      108 l
        0x0000377f6b6b6b00ULL, //      109 m
        0x00003b6666666600ULL, //      110 n
        0x00003e6363633e00ULL, //      111 o
        0x00003b66663e060fULL, //      112 p
        0x00006e33333e3078ULL, //      113 q
        0x00003b6e06060f00ULL, //      114 r
        0x00007e033e603f00ULL, //      115 s
        0x0c0c3f0c0c6c3800ULL, //      116 t
        0x0000333333336e00ULL, //      117 u
        0x0000636363361c00ULL, //      118 v
        0x0000636b6b7f3600ULL, //      119 w
        0x000063361c366300ULL, //      120 x
        0x00006363637e603fULL, //      121 y
        0x00007e32184c7e00ULL, //      122 z
        0x7018180e18187000ULL, //      123 {
        0x1818181818181800ULL, //      124 |
        0x0e18187018180e00ULL, //      125 }
        0x6e3b000000000000ULL, //      126 ~
        0x003e633f63673b00ULL  //      127 
};
