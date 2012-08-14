.file "isrs.s"
.text
.p2align 2,,3
.extern default_isr
.globl	_asm_isr_0
_asm_isr_0:
cli
pushl	$0x0
pushl	$0
jmp	isr_default_func


.globl	_asm_isr_1
_asm_isr_1:
cli
pushl	$0x0
pushl	$1
jmp	isr_default_func


.globl	_asm_isr_2
_asm_isr_2:
cli
pushl	$0x0
pushl	$2
jmp	isr_default_func


.globl	_asm_isr_3
_asm_isr_3:
cli
pushl	$0x0
pushl	$3
jmp	isr_default_func


.globl	_asm_isr_4
_asm_isr_4:
cli
pushl	$0x0
pushl	$4
jmp	isr_default_func


.globl	_asm_isr_5
_asm_isr_5:
cli
pushl	$0x0
pushl	$5
jmp	isr_default_func


.globl	_asm_isr_6
_asm_isr_6:
cli
pushl	$0x0
pushl	$6
jmp	isr_default_func


.globl	_asm_isr_7
_asm_isr_7:
cli
pushl	$0x0
pushl	$7
jmp	isr_default_func


.globl	_asm_isr_8
_asm_isr_8:
cli
pushl	$8
jmp	isr_default_func


.globl	_asm_isr_9
_asm_isr_9:
cli
pushl	$0x0
pushl	$9
jmp	isr_default_func


.globl	_asm_isr_10
_asm_isr_10:
cli
pushl	$10
jmp	isr_default_func


.globl	_asm_isr_11
_asm_isr_11:
cli
pushl	$11
jmp	isr_default_func


.globl	_asm_isr_12
_asm_isr_12:
cli
pushl	$12
jmp	isr_default_func


.globl	_asm_isr_13
_asm_isr_13:
cli
pushl	$13
jmp	isr_default_func


.globl	_asm_isr_14
_asm_isr_14:
cli
pushl	$14
jmp	isr_default_func


.globl	_asm_isr_15
_asm_isr_15:
cli
pushl	$0x0
pushl	$15
jmp	isr_default_func


.globl	_asm_isr_16
_asm_isr_16:
cli
pushl	$0x0
pushl	$16
jmp	isr_default_func


.globl	_asm_isr_17
_asm_isr_17:
cli
pushl	$0x0
pushl	$17
jmp	isr_default_func


.globl	_asm_isr_18
_asm_isr_18:
cli
pushl	$0x0
pushl	$18
jmp	isr_default_func


.globl	_asm_isr_19
_asm_isr_19:
cli
pushl	$0x0
pushl	$19
jmp	isr_default_func


.globl	_asm_isr_20
_asm_isr_20:
cli
pushl	$0x0
pushl	$20
jmp	isr_default_func


.globl	_asm_isr_21
_asm_isr_21:
cli
pushl	$0x0
pushl	$21
jmp	isr_default_func


.globl	_asm_isr_22
_asm_isr_22:
cli
pushl	$0x0
pushl	$22
jmp	isr_default_func


.globl	_asm_isr_23
_asm_isr_23:
cli
pushl	$0x0
pushl	$23
jmp	isr_default_func


.globl	_asm_isr_24
_asm_isr_24:
cli
pushl	$0x0
pushl	$24
jmp	isr_default_func


.globl	_asm_isr_25
_asm_isr_25:
cli
pushl	$0x0
pushl	$25
jmp	isr_default_func


.globl	_asm_isr_26
_asm_isr_26:
cli
pushl	$0x0
pushl	$26
jmp	isr_default_func


.globl	_asm_isr_27
_asm_isr_27:
cli
pushl	$0x0
pushl	$27
jmp	isr_default_func


.globl	_asm_isr_28
_asm_isr_28:
cli
pushl	$0x0
pushl	$28
jmp	isr_default_func


.globl	_asm_isr_29
_asm_isr_29:
cli
pushl	$0x0
pushl	$29
jmp	isr_default_func


.globl	_asm_isr_30
_asm_isr_30:
cli
pushl	$0x0
pushl	$30
jmp	isr_default_func


.globl	_asm_isr_31
_asm_isr_31:
cli
pushl	$0x0
pushl	$31
jmp	isr_default_func


.globl	_asm_isr_32 /*clock(pit)*/
_asm_isr_32:
cli
pushl	$0x0
pushl	$32
jmp	isr_default_func


.globl	_asm_isr_33  /*clavier*/
_asm_isr_33:
cli
pushl	$0x0
pushl	$33
jmp	isr_default_func


.globl	_asm_isr_34
_asm_isr_34:
cli
pushl	$0x0
pushl	$34
jmp	isr_default_func


.globl	_asm_isr_35
_asm_isr_35:
cli
pushl	$0x0
pushl	$35
jmp	isr_default_func


.globl	_asm_isr_36
_asm_isr_36:
cli
pushl	$0x0
pushl	$36
jmp	isr_default_func


.globl	_asm_isr_37
_asm_isr_37:
cli
pushl	$0x0
pushl	$37
jmp	isr_default_func


.globl	_asm_isr_38
_asm_isr_38:
cli
pushl	$0x0
pushl	$38
jmp	isr_default_func


.globl	_asm_isr_39
_asm_isr_39:
cli
pushl	$0x0
pushl	$39
jmp	isr_default_func


.globl	_asm_isr_40
_asm_isr_40:
cli
pushl	$0x0
pushl	$40
jmp	isr_default_func


.globl	_asm_isr_41
_asm_isr_41:
cli
pushl	$0x0
pushl	$41
jmp	isr_default_func


.globl	_asm_isr_42
_asm_isr_42:
cli
pushl	$0x0
pushl	$42
jmp	isr_default_func


.globl	_asm_isr_43
_asm_isr_43:
cli
pushl	$0x0
pushl	$43
jmp	isr_default_func


.globl	_asm_isr_44
_asm_isr_44:
cli
pushl	$0x0
pushl	$44
jmp	isr_default_func


.globl	_asm_isr_45
_asm_isr_45:
cli
pushl	$0x0
pushl	$45
jmp	isr_default_func


.globl	_asm_isr_46
_asm_isr_46:
cli
pushl	$0x0
pushl	$46
jmp	isr_default_func


.globl	_asm_isr_47
_asm_isr_47:
cli
pushl	$0x0
pushl	$47
jmp	isr_default_func


.globl	_asm_isr_48
_asm_isr_48:
cli
pushl	$0x0
pushl	$48
jmp	isr_default_func


.globl	_asm_isr_49
_asm_isr_49:
cli
pushl	$0x0
pushl	$49
jmp	isr_default_func


.globl	_asm_isr_50
_asm_isr_50:
cli
pushl	$0x0
pushl	$50
jmp	isr_default_func


.globl	_asm_isr_51
_asm_isr_51:
cli
pushl	$0x0
pushl	$51
jmp	isr_default_func


.globl	_asm_isr_52
_asm_isr_52:
cli
pushl	$0x0
pushl	$52
jmp	isr_default_func


.globl	_asm_isr_53
_asm_isr_53:
cli
pushl	$0x0
pushl	$53
jmp	isr_default_func


.globl	_asm_isr_54
_asm_isr_54:
cli
pushl	$0x0
pushl	$54
jmp	isr_default_func


.globl	_asm_isr_55
_asm_isr_55:
cli
pushl	$0x0
pushl	$55
jmp	isr_default_func


.globl	_asm_isr_56
_asm_isr_56:
cli
pushl	$0x0
pushl	$56
jmp	isr_default_func


.globl	_asm_isr_57
_asm_isr_57:
cli
pushl	$0x0
pushl	$57
jmp	isr_default_func


.globl	_asm_isr_58
_asm_isr_58:
cli
pushl	$0x0
pushl	$58
jmp	isr_default_func


.globl	_asm_isr_59
_asm_isr_59:
cli
pushl	$0x0
pushl	$59
jmp	isr_default_func


.globl	_asm_isr_60
_asm_isr_60:
cli
pushl	$0x0
pushl	$60
jmp	isr_default_func


.globl	_asm_isr_61
_asm_isr_61:
cli
pushl	$0x0
pushl	$61
jmp	isr_default_func


.globl	_asm_isr_62
_asm_isr_62:
cli
pushl	$0x0
pushl	$62
jmp	isr_default_func


.globl	_asm_isr_63
_asm_isr_63:
cli
pushl	$0x0
pushl	$63
jmp	isr_default_func


.globl	_asm_isr_64
_asm_isr_64:
cli
pushl	$0x0
pushl	$64
jmp	isr_default_func


.globl	_asm_isr_65
_asm_isr_65:
cli
pushl	$0x0
pushl	$65
jmp	isr_default_func


.globl	_asm_isr_66
_asm_isr_66:
cli
pushl	$0x0
pushl	$66
jmp	isr_default_func


.globl	_asm_isr_67
_asm_isr_67:
cli
pushl	$0x0
pushl	$67
jmp	isr_default_func


.globl	_asm_isr_68
_asm_isr_68:
cli
pushl	$0x0
pushl	$68
jmp	isr_default_func


.globl	_asm_isr_69
_asm_isr_69:
cli
pushl	$0x0
pushl	$69
jmp	isr_default_func


.globl	_asm_isr_70
_asm_isr_70:
cli
pushl	$0x0
pushl	$70
jmp	isr_default_func


.globl	_asm_isr_71
_asm_isr_71:
cli
pushl	$0x0
pushl	$71
jmp	isr_default_func


.globl	_asm_isr_72
_asm_isr_72:
cli
pushl	$0x0
pushl	$72
jmp	isr_default_func


.globl	_asm_isr_73
_asm_isr_73:
cli
pushl	$0x0
pushl	$73
jmp	isr_default_func


.globl	_asm_isr_74
_asm_isr_74:
cli
pushl	$0x0
pushl	$74
jmp	isr_default_func


.globl	_asm_isr_75
_asm_isr_75:
cli
pushl	$0x0
pushl	$75
jmp	isr_default_func


.globl	_asm_isr_76
_asm_isr_76:
cli
pushl	$0x0
pushl	$76
jmp	isr_default_func


.globl	_asm_isr_77
_asm_isr_77:
cli
pushl	$0x0
pushl	$77
jmp	isr_default_func


.globl	_asm_isr_78
_asm_isr_78:
cli
pushl	$0x0
pushl	$78
jmp	isr_default_func


.globl	_asm_isr_79
_asm_isr_79:
cli
pushl	$0x0
pushl	$79
jmp	isr_default_func


.globl	_asm_isr_80
_asm_isr_80:
cli
pushl	$0x0
pushl	$80
jmp	isr_default_func


.globl	_asm_isr_81
_asm_isr_81:
cli
pushl	$0x0
pushl	$81
jmp	isr_default_func


.globl	_asm_isr_82
_asm_isr_82:
cli
pushl	$0x0
pushl	$82
jmp	isr_default_func


.globl	_asm_isr_83
_asm_isr_83:
cli
pushl	$0x0
pushl	$83
jmp	isr_default_func


.globl	_asm_isr_84
_asm_isr_84:
cli
pushl	$0x0
pushl	$84
jmp	isr_default_func


.globl	_asm_isr_85
_asm_isr_85:
cli
pushl	$0x0
pushl	$85
jmp	isr_default_func


.globl	_asm_isr_86
_asm_isr_86:
cli
pushl	$0x0
pushl	$86
jmp	isr_default_func


.globl	_asm_isr_87
_asm_isr_87:
cli
pushl	$0x0
pushl	$87
jmp	isr_default_func


.globl	_asm_isr_88
_asm_isr_88:
cli
pushl	$0x0
pushl	$88
jmp	isr_default_func


.globl	_asm_isr_89
_asm_isr_89:
cli
pushl	$0x0
pushl	$89
jmp	isr_default_func


.globl	_asm_isr_90
_asm_isr_90:
cli
pushl	$0x0
pushl	$90
jmp	isr_default_func


.globl	_asm_isr_91
_asm_isr_91:
cli
pushl	$0x0
pushl	$91
jmp	isr_default_func


.globl	_asm_isr_92
_asm_isr_92:
cli
pushl	$0x0
pushl	$92
jmp	isr_default_func


.globl	_asm_isr_93
_asm_isr_93:
cli
pushl	$0x0
pushl	$93
jmp	isr_default_func


.globl	_asm_isr_94
_asm_isr_94:
cli
pushl	$0x0
pushl	$94
jmp	isr_default_func


.globl	_asm_isr_95
_asm_isr_95:
cli
pushl	$0x0
pushl	$95
jmp	isr_default_func


.globl	_asm_isr_96
_asm_isr_96:
cli
pushl	$0x0
pushl	$96
jmp	isr_default_func


.globl	_asm_isr_97
_asm_isr_97:
cli
pushl	$0x0
pushl	$97
jmp	isr_default_func


.globl	_asm_isr_98
_asm_isr_98:
cli
pushl	$0x0
pushl	$98
jmp	isr_default_func


.globl	_asm_isr_99
_asm_isr_99:
cli
pushl	$0x0
pushl	$99
jmp	isr_default_func


.globl	_asm_isr_100
_asm_isr_100:
cli
pushl	$0x0
pushl	$100
jmp	isr_default_func


.globl	_asm_isr_101
_asm_isr_101:
cli
pushl	$0x0
pushl	$101
jmp	isr_default_func


.globl	_asm_isr_102
_asm_isr_102:
cli
pushl	$0x0
pushl	$102
jmp	isr_default_func


.globl	_asm_isr_103
_asm_isr_103:
cli
pushl	$0x0
pushl	$103
jmp	isr_default_func


.globl	_asm_isr_104
_asm_isr_104:
cli
pushl	$0x0
pushl	$104
jmp	isr_default_func


.globl	_asm_isr_105
_asm_isr_105:
cli
pushl	$0x0
pushl	$105
jmp	isr_default_func


.globl	_asm_isr_106
_asm_isr_106:
cli
pushl	$0x0
pushl	$106
jmp	isr_default_func


.globl	_asm_isr_107
_asm_isr_107:
cli
pushl	$0x0
pushl	$107
jmp	isr_default_func


.globl	_asm_isr_108
_asm_isr_108:
cli
pushl	$0x0
pushl	$108
jmp	isr_default_func


.globl	_asm_isr_109
_asm_isr_109:
cli
pushl	$0x0
pushl	$109
jmp	isr_default_func


.globl	_asm_isr_110
_asm_isr_110:
cli
pushl	$0x0
pushl	$110
jmp	isr_default_func


.globl	_asm_isr_111
_asm_isr_111:
cli
pushl	$0x0
pushl	$111
jmp	isr_default_func


.globl	_asm_isr_112
_asm_isr_112:
cli
pushl	$0x0
pushl	$112
jmp	isr_default_func


.globl	_asm_isr_113
_asm_isr_113:
cli
pushl	$0x0
pushl	$113
jmp	isr_default_func


.globl	_asm_isr_114
_asm_isr_114:
cli
pushl	$0x0
pushl	$114
jmp	isr_default_func


.globl	_asm_isr_115
_asm_isr_115:
cli
pushl	$0x0
pushl	$115
jmp	isr_default_func


.globl	_asm_isr_116
_asm_isr_116:
cli
pushl	$0x0
pushl	$116
jmp	isr_default_func


.globl	_asm_isr_117
_asm_isr_117:
cli
pushl	$0x0
pushl	$117
jmp	isr_default_func


.globl	_asm_isr_118
_asm_isr_118:
cli
pushl	$0x0
pushl	$118
jmp	isr_default_func


.globl	_asm_isr_119
_asm_isr_119:
cli
pushl	$0x0
pushl	$119
jmp	isr_default_func


.globl	_asm_isr_120
_asm_isr_120:
cli
pushl	$0x0
pushl	$120
jmp	isr_default_func


.globl	_asm_isr_121
_asm_isr_121:
cli
pushl	$0x0
pushl	$121
jmp	isr_default_func


.globl	_asm_isr_122
_asm_isr_122:
cli
pushl	$0x0
pushl	$122
jmp	isr_default_func


.globl	_asm_isr_123
_asm_isr_123:
cli
pushl	$0x0
pushl	$123
jmp	isr_default_func


.globl	_asm_isr_124
_asm_isr_124:
cli
pushl	$0x0
pushl	$124
jmp	isr_default_func


.globl	_asm_isr_125
_asm_isr_125:
cli
pushl	$0x0
pushl	$125
jmp	isr_default_func


.globl	_asm_isr_126
_asm_isr_126:
cli
pushl	$0x0
pushl	$126
jmp	isr_default_func


.globl	_asm_isr_127
_asm_isr_127:
cli
pushl	$0x0
pushl	$127
jmp	isr_default_func


.globl	_asm_isr_128
_asm_isr_128:
cli
pushl	$0x0
pushl	$128
jmp	isr_default_func


.globl	_asm_isr_129
_asm_isr_129:
cli
pushl	$0x0
pushl	$129
jmp	isr_default_func


.globl	_asm_isr_130
_asm_isr_130:
cli
pushl	$0x0
pushl	$130
jmp	isr_default_func


.globl	_asm_isr_131
_asm_isr_131:
cli
pushl	$0x0
pushl	$131
jmp	isr_default_func


.globl	_asm_isr_132
_asm_isr_132:
cli
pushl	$0x0
pushl	$132
jmp	isr_default_func


.globl	_asm_isr_133
_asm_isr_133:
cli
pushl	$0x0
pushl	$133
jmp	isr_default_func


.globl	_asm_isr_134
_asm_isr_134:
cli
pushl	$0x0
pushl	$134
jmp	isr_default_func


.globl	_asm_isr_135
_asm_isr_135:
cli
pushl	$0x0
pushl	$135
jmp	isr_default_func


.globl	_asm_isr_136
_asm_isr_136:
cli
pushl	$0x0
pushl	$136
jmp	isr_default_func


.globl	_asm_isr_137
_asm_isr_137:
cli
pushl	$0x0
pushl	$137
jmp	isr_default_func


.globl	_asm_isr_138
_asm_isr_138:
cli
pushl	$0x0
pushl	$138
jmp	isr_default_func


.globl	_asm_isr_139
_asm_isr_139:
cli
pushl	$0x0
pushl	$139
jmp	isr_default_func


.globl	_asm_isr_140
_asm_isr_140:
cli
pushl	$0x0
pushl	$140
jmp	isr_default_func


.globl	_asm_isr_141
_asm_isr_141:
cli
pushl	$0x0
pushl	$141
jmp	isr_default_func


.globl	_asm_isr_142
_asm_isr_142:
cli
pushl	$0x0
pushl	$142
jmp	isr_default_func


.globl	_asm_isr_143
_asm_isr_143:
cli
pushl	$0x0
pushl	$143
jmp	isr_default_func


.globl	_asm_isr_144
_asm_isr_144:
cli
pushl	$0x0
pushl	$144
jmp	isr_default_func


.globl	_asm_isr_145
_asm_isr_145:
cli
pushl	$0x0
pushl	$145
jmp	isr_default_func


.globl	_asm_isr_146
_asm_isr_146:
cli
pushl	$0x0
pushl	$146
jmp	isr_default_func


.globl	_asm_isr_147
_asm_isr_147:
cli
pushl	$0x0
pushl	$147
jmp	isr_default_func


.globl	_asm_isr_148
_asm_isr_148:
cli
pushl	$0x0
pushl	$148
jmp	isr_default_func


.globl	_asm_isr_149
_asm_isr_149:
cli
pushl	$0x0
pushl	$149
jmp	isr_default_func


.globl	_asm_isr_150
_asm_isr_150:
cli
pushl	$0x0
pushl	$150
jmp	isr_default_func


.globl	_asm_isr_151
_asm_isr_151:
cli
pushl	$0x0
pushl	$151
jmp	isr_default_func


.globl	_asm_isr_152
_asm_isr_152:
cli
pushl	$0x0
pushl	$152
jmp	isr_default_func


.globl	_asm_isr_153
_asm_isr_153:
cli
pushl	$0x0
pushl	$153
jmp	isr_default_func


.globl	_asm_isr_154
_asm_isr_154:
cli
pushl	$0x0
pushl	$154
jmp	isr_default_func


.globl	_asm_isr_155
_asm_isr_155:
cli
pushl	$0x0
pushl	$155
jmp	isr_default_func


.globl	_asm_isr_156
_asm_isr_156:
cli
pushl	$0x0
pushl	$156
jmp	isr_default_func


.globl	_asm_isr_157
_asm_isr_157:
cli
pushl	$0x0
pushl	$157
jmp	isr_default_func


.globl	_asm_isr_158
_asm_isr_158:
cli
pushl	$0x0
pushl	$158
jmp	isr_default_func


.globl	_asm_isr_159
_asm_isr_159:
cli
pushl	$0x0
pushl	$159
jmp	isr_default_func


.globl	_asm_isr_160
_asm_isr_160:
cli
pushl	$0x0
pushl	$160
jmp	isr_default_func


.globl	_asm_isr_161
_asm_isr_161:
cli
pushl	$0x0
pushl	$161
jmp	isr_default_func


.globl	_asm_isr_162
_asm_isr_162:
cli
pushl	$0x0
pushl	$162
jmp	isr_default_func


.globl	_asm_isr_163
_asm_isr_163:
cli
pushl	$0x0
pushl	$163
jmp	isr_default_func


.globl	_asm_isr_164
_asm_isr_164:
cli
pushl	$0x0
pushl	$164
jmp	isr_default_func


.globl	_asm_isr_165
_asm_isr_165:
cli
pushl	$0x0
pushl	$165
jmp	isr_default_func


.globl	_asm_isr_166
_asm_isr_166:
cli
pushl	$0x0
pushl	$166
jmp	isr_default_func


.globl	_asm_isr_167
_asm_isr_167:
cli
pushl	$0x0
pushl	$167
jmp	isr_default_func


.globl	_asm_isr_168
_asm_isr_168:
cli
pushl	$0x0
pushl	$168
jmp	isr_default_func


.globl	_asm_isr_169
_asm_isr_169:
cli
pushl	$0x0
pushl	$169
jmp	isr_default_func


.globl	_asm_isr_170
_asm_isr_170:
cli
pushl	$0x0
pushl	$170
jmp	isr_default_func


.globl	_asm_isr_171
_asm_isr_171:
cli
pushl	$0x0
pushl	$171
jmp	isr_default_func


.globl	_asm_isr_172
_asm_isr_172:
cli
pushl	$0x0
pushl	$172
jmp	isr_default_func


.globl	_asm_isr_173
_asm_isr_173:
cli
pushl	$0x0
pushl	$173
jmp	isr_default_func


.globl	_asm_isr_174
_asm_isr_174:
cli
pushl	$0x0
pushl	$174
jmp	isr_default_func


.globl	_asm_isr_175
_asm_isr_175:
cli
pushl	$0x0
pushl	$175
jmp	isr_default_func


.globl	_asm_isr_176
_asm_isr_176:
cli
pushl	$0x0
pushl	$176
jmp	isr_default_func


.globl	_asm_isr_177
_asm_isr_177:
cli
pushl	$0x0
pushl	$177
jmp	isr_default_func


.globl	_asm_isr_178
_asm_isr_178:
cli
pushl	$0x0
pushl	$178
jmp	isr_default_func


.globl	_asm_isr_179
_asm_isr_179:
cli
pushl	$0x0
pushl	$179
jmp	isr_default_func


.globl	_asm_isr_180
_asm_isr_180:
cli
pushl	$0x0
pushl	$180
jmp	isr_default_func


.globl	_asm_isr_181
_asm_isr_181:
cli
pushl	$0x0
pushl	$181
jmp	isr_default_func


.globl	_asm_isr_182
_asm_isr_182:
cli
pushl	$0x0
pushl	$182
jmp	isr_default_func


.globl	_asm_isr_183
_asm_isr_183:
cli
pushl	$0x0
pushl	$183
jmp	isr_default_func


.globl	_asm_isr_184
_asm_isr_184:
cli
pushl	$0x0
pushl	$184
jmp	isr_default_func


.globl	_asm_isr_185
_asm_isr_185:
cli
pushl	$0x0
pushl	$185
jmp	isr_default_func


.globl	_asm_isr_186
_asm_isr_186:
cli
pushl	$0x0
pushl	$186
jmp	isr_default_func


.globl	_asm_isr_187
_asm_isr_187:
cli
pushl	$0x0
pushl	$187
jmp	isr_default_func


.globl	_asm_isr_188
_asm_isr_188:
cli
pushl	$0x0
pushl	$188
jmp	isr_default_func


.globl	_asm_isr_189
_asm_isr_189:
cli
pushl	$0x0
pushl	$189
jmp	isr_default_func


.globl	_asm_isr_190
_asm_isr_190:
cli
pushl	$0x0
pushl	$190
jmp	isr_default_func


.globl	_asm_isr_191
_asm_isr_191:
cli
pushl	$0x0
pushl	$191
jmp	isr_default_func


.globl	_asm_isr_192
_asm_isr_192:
cli
pushl	$0x0
pushl	$192
jmp	isr_default_func


.globl	_asm_isr_193
_asm_isr_193:
cli
pushl	$0x0
pushl	$193
jmp	isr_default_func


.globl	_asm_isr_194
_asm_isr_194:
cli
pushl	$0x0
pushl	$194
jmp	isr_default_func


.globl	_asm_isr_195
_asm_isr_195:
cli
pushl	$0x0
pushl	$195
jmp	isr_default_func


.globl	_asm_isr_196
_asm_isr_196:
cli
pushl	$0x0
pushl	$196
jmp	isr_default_func


.globl	_asm_isr_197
_asm_isr_197:
cli
pushl	$0x0
pushl	$197
jmp	isr_default_func


.globl	_asm_isr_198
_asm_isr_198:
cli
pushl	$0x0
pushl	$198
jmp	isr_default_func


.globl	_asm_isr_199
_asm_isr_199:
cli
pushl	$0x0
pushl	$199
jmp	isr_default_func


.globl	_asm_isr_200
_asm_isr_200:
cli
pushl	$0x0
pushl	$200
jmp	isr_default_func


.globl	_asm_isr_201
_asm_isr_201:
cli
pushl	$0x0
pushl	$201
jmp	isr_default_func


.globl	_asm_isr_202
_asm_isr_202:
cli
pushl	$0x0
pushl	$202
jmp	isr_default_func


.globl	_asm_isr_203
_asm_isr_203:
cli
pushl	$0x0
pushl	$203
jmp	isr_default_func


.globl	_asm_isr_204
_asm_isr_204:
cli
pushl	$0x0
pushl	$204
jmp	isr_default_func


.globl	_asm_isr_205
_asm_isr_205:
cli
pushl	$0x0
pushl	$205
jmp	isr_default_func


.globl	_asm_isr_206
_asm_isr_206:
cli
pushl	$0x0
pushl	$206
jmp	isr_default_func


.globl	_asm_isr_207
_asm_isr_207:
cli
pushl	$0x0
pushl	$207
jmp	isr_default_func


.globl	_asm_isr_208
_asm_isr_208:
cli
pushl	$0x0
pushl	$208
jmp	isr_default_func


.globl	_asm_isr_209
_asm_isr_209:
cli
pushl	$0x0
pushl	$209
jmp	isr_default_func


.globl	_asm_isr_210
_asm_isr_210:
cli
pushl	$0x0
pushl	$210
jmp	isr_default_func


.globl	_asm_isr_211
_asm_isr_211:
cli
pushl	$0x0
pushl	$211
jmp	isr_default_func


.globl	_asm_isr_212
_asm_isr_212:
cli
pushl	$0x0
pushl	$212
jmp	isr_default_func


.globl	_asm_isr_213
_asm_isr_213:
cli
pushl	$0x0
pushl	$213
jmp	isr_default_func


.globl	_asm_isr_214
_asm_isr_214:
cli
pushl	$0x0
pushl	$214
jmp	isr_default_func


.globl	_asm_isr_215
_asm_isr_215:
cli
pushl	$0x0
pushl	$215
jmp	isr_default_func


.globl	_asm_isr_216
_asm_isr_216:
cli
pushl	$0x0
pushl	$216
jmp	isr_default_func


.globl	_asm_isr_217
_asm_isr_217:
cli
pushl	$0x0
pushl	$217
jmp	isr_default_func


.globl	_asm_isr_218
_asm_isr_218:
cli
pushl	$0x0
pushl	$218
jmp	isr_default_func


.globl	_asm_isr_219
_asm_isr_219:
cli
pushl	$0x0
pushl	$219
jmp	isr_default_func


.globl	_asm_isr_220
_asm_isr_220:
cli
pushl	$0x0
pushl	$220
jmp	isr_default_func


.globl	_asm_isr_221
_asm_isr_221:
cli
pushl	$0x0
pushl	$221
jmp	isr_default_func


.globl	_asm_isr_222
_asm_isr_222:
cli
pushl	$0x0
pushl	$222
jmp	isr_default_func


.globl	_asm_isr_223
_asm_isr_223:
cli
pushl	$0x0
pushl	$223
jmp	isr_default_func


.globl	_asm_isr_224
_asm_isr_224:
cli
pushl	$0x0
pushl	$224
jmp	isr_default_func


.globl	_asm_isr_225
_asm_isr_225:
cli
pushl	$0x0
pushl	$225
jmp	isr_default_func


.globl	_asm_isr_226
_asm_isr_226:
cli
pushl	$0x0
pushl	$226
jmp	isr_default_func


.globl	_asm_isr_227
_asm_isr_227:
cli
pushl	$0x0
pushl	$227
jmp	isr_default_func


.globl	_asm_isr_228
_asm_isr_228:
cli
pushl	$0x0
pushl	$228
jmp	isr_default_func


.globl	_asm_isr_229
_asm_isr_229:
cli
pushl	$0x0
pushl	$229
jmp	isr_default_func


.globl	_asm_isr_230
_asm_isr_230:
cli
pushl	$0x0
pushl	$230
jmp	isr_default_func


.globl	_asm_isr_231
_asm_isr_231:
cli
pushl	$0x0
pushl	$231
jmp	isr_default_func


.globl	_asm_isr_232
_asm_isr_232:
cli
pushl	$0x0
pushl	$232
jmp	isr_default_func


.globl	_asm_isr_233
_asm_isr_233:
cli
pushl	$0x0
pushl	$233
jmp	isr_default_func


.globl	_asm_isr_234
_asm_isr_234:
cli
pushl	$0x0
pushl	$234
jmp	isr_default_func


.globl	_asm_isr_235
_asm_isr_235:
cli
pushl	$0x0
pushl	$235
jmp	isr_default_func


.globl	_asm_isr_236
_asm_isr_236:
cli
pushl	$0x0
pushl	$236
jmp	isr_default_func


.globl	_asm_isr_237
_asm_isr_237:
cli
pushl	$0x0
pushl	$237
jmp	isr_default_func


.globl	_asm_isr_238
_asm_isr_238:
cli
pushl	$0x0
pushl	$238
jmp	isr_default_func


.globl	_asm_isr_239
_asm_isr_239:
cli
pushl	$0x0
pushl	$239
jmp	isr_default_func


.globl	_asm_isr_240
_asm_isr_240:
cli
pushl	$0x0
pushl	$240
jmp	isr_default_func


.globl	_asm_isr_241
_asm_isr_241:
cli
pushl	$0x0
pushl	$241
jmp	isr_default_func


.globl	_asm_isr_242
_asm_isr_242:
cli
pushl	$0x0
pushl	$242
jmp	isr_default_func


.globl	_asm_isr_243
_asm_isr_243:
cli
pushl	$0x0
pushl	$243
jmp	isr_default_func


.globl	_asm_isr_244
_asm_isr_244:
cli
pushl	$0x0
pushl	$244
jmp	isr_default_func


.globl	_asm_isr_245
_asm_isr_245:
cli
pushl	$0x0
pushl	$245
jmp	isr_default_func


.globl	_asm_isr_246
_asm_isr_246:
cli
pushl	$0x0
pushl	$246
jmp	isr_default_func


.globl	_asm_isr_247
_asm_isr_247:
cli
pushl	$0x0
pushl	$247
jmp	isr_default_func


.globl	_asm_isr_248
_asm_isr_248:
cli
pushl	$0x0
pushl	$248
jmp	isr_default_func


.globl	_asm_isr_249
_asm_isr_249:
cli
pushl	$0x0
pushl	$249
jmp	isr_default_func


.globl	_asm_isr_250
_asm_isr_250:
cli
pushl	$0x0
pushl	$250
jmp	isr_default_func


.globl	_asm_isr_251
_asm_isr_251:
cli
pushl	$0x0
pushl	$251
jmp	isr_default_func


.globl	_asm_isr_252
_asm_isr_252:
cli
pushl	$0x0
pushl	$252
jmp	isr_default_func


.globl	_asm_isr_253
_asm_isr_253:
cli
pushl	$0x0
pushl	$253
jmp	isr_default_func


.globl	_asm_isr_254
_asm_isr_254:
cli
pushl	$0x0
pushl	$254
jmp	isr_default_func


.globl	_asm_isr_255
_asm_isr_255:
cli
pushl	$0x0
pushl	$255
jmp	isr_default_func

isr_default_func:
pushal
push	%ds
push	%es
push	%fs
push	%gs
mov	$0x10, %ax
mov	%ax, %ds
mov	%ax, %fs
mov	%ax, %es
mov	%ax, %gs
movl	%esp, %eax
pushl	%eax
movl	$_default_isr, %eax
call	*%eax
popl	%eax
pop	%gs
pop	%fs
pop	%es
pop	%ds
popal
addl	$8, %esp
iret
