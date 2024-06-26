#!/usr/bin/env bash 
# 

###############
# proton beam
###############

# IAEA (Ishibashi)
#
# bid=105-107 (KEK 0.8,1.5,3.0GeV proton)

exp_data_proton3.824GeV_C_IAEA() {

/usr/bin/printf "            DBRecords: [ 164978, 164979, 164980, 164981, 164982, 164983 ]"

}

#
# No data on Cu; closest is Fe
#
exp_data_proton3.824GeV_Fe_IAEA() {

/usr/bin/printf "            DBRecords: [ 164962, 164963, 164964, 164965, 164966, 164967 ]"

}

exp_data_proton3.824GeV_Pb_IAEA() {

/usr/bin/printf "            DBRecords: [ 189636, 189637, 189638, 189639, 189640, 189641 ]"

}

# HARP
#
# bid=37-41 (HARP/PC 3,5,8,8.9,12 GeV/c proton)

exp_data_proton3.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 10538, 10539, 10540, 10541, 10542, 10543, 10544, 10545, 10546, 10547, 10548, 10549, 10550,\n"
/usr/bin/printf "                         10590, 10591, 10592, 10593, 10594, 10595, 10596, 10597, 10598, 10599, 10600, 10601, 10602,\n"
/usr/bin/printf "                         200000, 200001, 200002, 200003 ]"

}

exp_data_proton3.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10642, 10643, 10644, 10645, 10646, 10647, 10648, 10649, 10650, 10651, 10652, 10653, 10654,\n"
/usr/bin/printf "                         10694, 10695, 10696, 10697, 10698, 10699, 10700, 10701, 10702, 10703, 10704, 10705, 10706,\n"
/usr/bin/printf "                         200048, 200049, 200050, 200051 ]"

}

exp_data_proton3.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10746, 10747, 10748, 10749, 10750, 10751, 10752, 10753, 10754, 10755, 10756, 10757, 10758,\n"
/usr/bin/printf "                         10798, 10799, 10800, 10801, 10802, 10803, 10804, 10805, 10806, 10807, 10808, 10809, 10810,\n" 
/usr/bin/printf "                         200096, 200097, 200098, 200099 ]"

}

exp_data_proton5.0GeV_C_HARP() {

# NEW (!!!) record ids for 5.0GeV/c proton on C (HARP data) 
# (seleced by bid=38)
/usr/bin/printf "            DBRecords: [ 10551, 10552, 10553, 10554, 10555, 10556, 10557, 10558, 10559, 10560, 10561, 10562, 10563,\n"
/usr/bin/printf "                         10603, 10604, 10605, 10606, 10607, 10608, 10609, 10610, 10611, 10612, 10613, 10614, 10615,\n"
/usr/bin/printf "                         200004, 200005, 200006, 200007 ]"

}

exp_data_proton5.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10655, 10656, 10657, 10658, 10659, 10660, 10661, 10662, 10663, 10664, 10665, 10666, 10667, \n"
/usr/bin/printf "                         10707, 10708, 10709, 10710, 10711, 10712, 10713, 10714, 10715, 10716, 10717, 10718, 10719, \n"
/usr/bin/printf "                         200052, 200053, 200054, 200055 ]"

}

exp_data_proton5.0GeV_Pb_HARP() {

# NEW (!!!) record ids for 5.0GeV/c proton on Pb (HARP data) 
# (seleced by bid=38)
/usr/bin/printf "            DBRecords: [ 10759, 10760, 10761, 10762, 10763, 10764, 10765, 10766, 10767, 10768, 10769, 10770, 10771, \n"
/usr/bin/printf "                         10811, 10812, 10813, 10814, 10815, 10816, 10817, 10818, 10819, 10820, 10821, 10822, 10823, \n"
/usr/bin/printf "                         200100, 200101, 200102, 200103 ]"

}

exp_data_proton8.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 10564, 10565, 10566, 10567, 10568, 10569, 10570, 10571, 10572, 10573, 10574, 10575, 10576, \n"
/usr/bin/printf "                         10616, 10617, 10618, 10619, 10620, 10621, 10622, 10623, 10624, 10625, 10626, 10627, 10628, \n"
/usr/bin/printf "                         200008, 200009, 200010,  200011 ]" 

}

exp_data_proton8.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10668, 10669, 10670, 10671, 10672, 10673, 10674, 10675, 10676, 10677, 10678, 10679, 10680, \n"
/usr/bin/printf "                         10720, 10721, 10722, 10723, 10724, 10725, 10726, 10727, 10728, 10729, 10730, 10731, 10732, \n"
/usr/bin/printf "                         200056, 200057, 200058, 200059 ]"

}

exp_data_proton8.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 10876,  10877,  10878,  10879, 10880, 10881, 10882, 10883, 10884, 10885, 10886, 10887, 10888, \n"
/usr/bin/printf "                         10928,  10929,  10930,  10931, 10932, 10933, 10934, 10935, 10936, 10937, 10938, 10939, 10940, \n"
/usr/bin/printf "                         200200, 200201, 200202, 200203, 200204, 200205, 200206, 200207, 200208, 200209, \n"
/usr/bin/printf "                         200210, 200211, 200212, 200213, 200214, 200215, 200216, 200217, 200218, 200219 ]"

}

exp_data_proton8.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10772, 10773, 10774, 10775, 10776, 10777, 10778, 10779, 10780, 10781, 10782, 10783, 10784, \n"
/usr/bin/printf "                         10824, 10825, 10826, 10827, 10828, 10829, 10830, 10831, 10832, 10833, 10834, 10835, 10836, \n"
/usr/bin/printf "                         200104, 200105, 200106, 200107 ]"

}

exp_data_proton12.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 10577, 10578, 10579, 10580, 10581, 10582, 10583, 10584, 10585, 10586, 10587, 10588, 10589, \n"
/usr/bin/printf "                         10629, 10630, 10631, 10632, 10633, 10634, 10635, 10636, 10637, 10638, 10639, 10640, 10641, \n"
/usr/bin/printf "                         200012, 200013, 200014, 200015 ]"

}

exp_data_proton12.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10681, 10682, 10683, 10684, 10685, 10686, 10687, 10688, 10689, 10690, 10691, 10692, 10693, \n"
/usr/bin/printf "                         10733, 10734, 10735, 10736, 10737, 10738, 10739, 10740, 10741, 10742, 10743, 10744, 10745, \n"
/usr/bin/printf "                         200060, 200061, 200062, 200063 ]"

}

exp_data_proton12.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10785, 10786, 10787, 10788, 10789, 10790, 10791, 10792, 10793, 10794, 10795, 10796, 10797, \n"
/usr/bin/printf "                         10837, 10838, 10839, 10840, 10841, 10842, 10843, 10844, 10845, 10946, 10847, 10848, 10849, \n"
/usr/bin/printf "                         200108, 200109, 200110, 200111 ]"

}


# ITEP
#
# bid=57 (7.5GeV/c proton), bid=70 (5GeV/c proton) 

exp_data_proton5.0GeV_C_ITEP() {

# NEW (!!!) record ids for 5.0GeV/c proton on C (ITEP771 data) - surprisingly, these are still OK !!!
# (selected by bid=70)
#
# NOTE: record=2401 (neutron production at 119deg) should be EXCLUDED since the first 4 data points look wrong
#
/usr/bin/printf "            DBRecords: [ 2339, 2340, 2341, 2342 ]"

}

# NOTE: can NOT find record on neutron production on Cu - need to explore/investigate
#       record 2488 that was listed here before is for 7.5GeV/c protob on Cu 
#       (BTW, same story of missing records on secondary neutrons for e.g. U... 
#        even if we haven't used it in the fits yet...)
#
exp_data_proton5.0GeV_Cu_ITEP() {

/usr/bin/printf "            DBRecords: [ 2422, 2423, 2424, 2425 ]"

}

exp_data_proton5.0GeV_Pb_ITEP() {

/usr/bin/printf "            DBRecords: [ 2515, 2516, 2517, 2518, 2573 ]"

}

exp_data_proton7.5GeV_C_ITEP() {

/usr/bin/printf "            DBRecords: [ 2371, 2372, 2373, 2374, 2375, 2376, 2377, 2378, 2379, 2380, \n"
/usr/bin/printf "                         2381, 2382, 2383, 2384, 2385, 2386, 2387, 2388, 2389, 2390, \n"
/usr/bin/printf "                         2391, 2392, 2393, 2394, 2395, 2396, 2397, 2398, 2399, \n"
/usr/bin/printf "                         2402, 2403, 2404, 2405 ]"

}

# NOTE: only 28 records here as id=2475 seems to be missing
exp_data_proton7.5GeV_Cu_ITEP() {

/usr/bin/printf "            DBRecords: [ 2454, 2455, 2456, 2457, 2458, 2459, 2460, 2461, 2462, 2463, \n"
/usr/bin/printf "                         2464, 2465, 2466, 2467, 2468, 2469, 2470, 2471, 2472, 2473, \n"
/usr/bin/printf "                         2474, 2476, 2477, 2478, 2479, 2480, 2481, 2482, \n"
/usr/bin/printf "                         2487, 2488, 2489, 2490 ]"

}

exp_data_proton7.5GeV_Pb_ITEP() {

/usr/bin/printf "            DBRecords: [ 2543, 2544, 2545, 2546, 2547, 2548, 2549, 2550, 2551, 2552, \n"
/usr/bin/printf "                         2553, 2554, 2555, 2556, 2557, 2558, 2559, 2560, 2561, 2562, \n"
/usr/bin/printf "                         2563, 2564, 2565, 2566, 2567, 2568, 2569, 2570, 2571, \n"
/usr/bin/printf "                         2574, 2575, 2576, 2577 ]"

}

# NA61
#
# bid=36 

exp_data_proton31.0GeV_C_NA61() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary K0s \n"
/usr/bin/printf "                         14572, 14573, 14574, 14575, 14576, 14577, 14578, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         14579, 14580, 14581, 14582, 14583, 14584, 14585, 14586, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         14587, 14588, 14589, 14590, 14591, 14592, 14593, 14594, \n"
/usr/bin/printf "                         // secondary Lambda (pid=3122); NOTE: do NOT use record for theta=300-420mrad \n"
/usr/bin/printf "                         14595, 14596, 14597, 14598, 14599, 14600, 14601, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         14603, 14604, 14605, 14606, 14607, 14608, 14609, 14610, 14611, \n"
/usr/bin/printf "                         14612, 14613, \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         14614, 14615, 14616, 14617, 14618, 14619, 14620, 14621, 14622, 14623, 14624, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         14625, 14626, 14627, 14628, 14629, 14630, 14631, 14632, 14633, 14634 \n"
/usr/bin/printf "                       ] \n"

}



# SAS M6E
#
# bid=12 (11 for K+, 10 for pi+)

exp_data_proton100.0GeV_C_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         9009, 9010, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         9011, 9012, 9013, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         9014, 9015, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         9017, 9018, \n" # do NOT use 9016 - will not rebin
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         9019, 9020 \n"
# /usr/bin/printf "                         // secondary antiproton \n"
# /usr/bin/printf "                         9021, 9022, 9023 \n" # do NOT use - will not rebin
/usr/bin/printf "                       ] \n"
 
}

exp_data_proton100.0GeV_Cu_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         9024, 9025, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         9026, 9027, 9028, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         9029, 9030, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         9031, 9032, 9033, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         9034, 9035, \n"
/usr/bin/printf "                         // secondary antiproton \n"
/usr/bin/printf "                         9036, 9037, 9038 \n"
/usr/bin/printf "                       ] \n"

}

exp_data_proton100.0GeV_Pb_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         9039, 9040, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         9041, 9042, 9043, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         9044, 9045, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         9046, 9047, 9048, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         9049, 9050, \n"
/usr/bin/printf "                         // secondary antiproton \n"
/usr/bin/printf "                         9051, 9052, 9053 \n"
/usr/bin/printf "                       ] \n"

}


# NA49
#
# bid=7

exp_data_proton158.0GeV_C_NA49() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "// integrated spectra for all seconadries - the first 5 are dN/dxF and the last 4 are d<pt>/dxF \n"	      
/usr/bin/printf "                         14649, 14650, 14651, 14652, 14653, 14654, 14655, 14656, 14657, \n"
/usr/bin/printf "// diff.spectra for pi- \n"
/usr/bin/printf "                         14658, 14659, 14660, 14661, 14662, 14663, 14664, 14665, 14666, \n"
/usr/bin/printf "                         14667, 14668, 14669, 14670, 14671, 14672, 14673, 14674, 14675, \n"
/usr/bin/printf "                         14676, 14677, 14678, 14679, 14680, 14681, 14682, \n"
/usr/bin/printf "// diff.spectra for pi+ \n"
/usr/bin/printf "                         14683, 14684, 14685, 14686, 14687, 14688, 14689, 14690, 14691, \n"
/usr/bin/printf "                         14692, 14693, 14694, 14695, 14696, 14697, 14698, 14699, 14700, \n"
/usr/bin/printf "                         14701, 14702, 14703, 14704, 14705, 14706, 14707, \n "
/usr/bin/printf "// diff.spectra for p \n"
/usr/bin/printf "                         14708, 14709, 14710, 14711, 14712, 14713, 14714, 14715, 14716, 14717, \n"
/usr/bin/printf "                         14718, 14719, 14720, 14721, 14722, 14723, 14724, 14725, 14726, 14727, \n"
/usr/bin/printf "                         14728, 14729, 14730, 14731, 14732, 14733, 14734, 14735, 14736, 14737, \n"
/usr/bin/printf "                         14738, 14739, 14740, 14741, 14742, 14743, 14744, 14745, 14746, 14747 \n"
/usr/bin/printf "                       ] \n"

}

#####################
# pi- beam (piminus)
#####################

# HARP
#
# bid=46-49 (HARP/PS 3,5,8,12GeV/c pi-)

exp_data_piminus3.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9264, 9265, 9266, 9267, 9268, 9269, 9270, 9271, 9272, 9273, 9274, 9275, 9276, \n"
/usr/bin/printf "                         9316, 9317, 9318, 9319, 9320, 9321, 9322, 9323, 9324, 9325, 9326, 9327, 9328, \n"
/usr/bin/printf "                         200016, 200017, 200018, 200019 ]"

}

exp_data_piminus3.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 9368, 9369, 9370, 9371, 9372, 9373, 9374, 9375, 9376, 9377, 9378, 9379, 9380, \n"
/usr/bin/printf "                         9420, 9421, 9422, 9423, 9424, 9425, 9426, 9427, 9428, 9429, 9430, 9431, 9432, \n"
/usr/bin/printf "                         200064, 200065, 200066, 200067 ]"

}

exp_data_piminus3.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 9472, 9473, 9474, 9475, 9476, 9477, 9478, 9479, 9480, 9481, 9482, 9483, 9484, \n"
/usr/bin/printf "                         9524, 9525, 9526, 9527, 9528, 9529, 9530, 9531, 9532, 9533, 9534, 9535, 9536, \n"
/usr/bin/printf "                         200112, 200113, 200114, 200115 ]"

}

exp_data_piminus5.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9277, 9278, 9279, 9280, 9281, 9282, 9283, 9284, 9285, 9286, 9287, 9288, 9289, \n"
/usr/bin/printf "                         9329, 9330, 9331, 9332, 9333, 9334, 9335, 9336, 9337, 9338, 9339, 9340, 9341, \n"
/usr/bin/printf "                         200020, 200021, 200022, 200023 ]"

}

exp_data_piminus5.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 9381, 9382, 16007, 16008, 9385, 9386, 9387, 9388, 9389, 9390, 9391, 9392, 9393, \n"
/usr/bin/printf "                         9433, 9434, 9435, 9436, 9437, 9438, 9439, 9440, 9441, 9442, 9443, 9444, 9445, \n"
/usr/bin/printf "                         200068, 200069, 200070, 200071 ]"

}

exp_data_piminus5.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 9589, 9590, 9591, 9592, 9593, 9594, 9595, 9596, 9597, 9598, 9599, 9600, 9601, \n"
/usr/bin/printf "                         9641, 9642, 9643, 9644, 9645, 9646, 9647, 9648, 9649, 9650, 9651, 9652, 9653 ]"

}

exp_data_piminus5.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 9485, 9486, 9487, 9488, 9489, 9490, 9491, 9492, 9493, 9494, 9495, 9496, 9497, \n"
/usr/bin/printf "                         9537, 9538, 9539, 9540, 9541, 9542, 9543, 9544, 9545, 9546, 9547, 9548, 9549, \n"
/usr/bin/printf "                         200116, 200117, 200118, 200119 ]"

}

exp_data_piminus8.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9290, 9291, 9292, 9293, 9294, 9295, 9296, 9297, 9298, 9299, 9300, 9301, 9302, \n"
/usr/bin/printf "                         9342, 9343, 9344, 9345, 9346, 9347, 9348, 9349, 9350, 9351, 9352, 9353, 9354, \n"
/usr/bin/printf "                         200024, 200025, 200026, 200027 ]"

}

exp_data_piminus8.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 9394, 9395, 9396, 9397, 9398, 9399, 9400, 9401, 9402, 9403, 9404, 9405, 9406, \n"
/usr/bin/printf "                         9446, 9447, 9448, 9449, 9450, 9451, 9452, 9453, 9454, 9455, 9456, 9457, 9458, \n"
/usr/bin/printf "                         200072, 200073, 200074, 200075 ]"

}

exp_data_piminus8.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 9602, 9603, 9604, 9605, 9606, 9607, 9608, 9609, 9610, 9611, 9612, 9613, 9614, \n"
/usr/bin/printf "                         9654, 9655, 9656, 9657, 9658, 9659, 9660, 9661, 9662, 9663, 9664, 9665, 9666 ]"
}

exp_data_piminus8.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 9498, 9499, 9500, 9501, 9502, 9503, 9504, 9505, 9506, 9507, 9508, 9509, 9510, \n"
/usr/bin/printf "                         9550, 9551, 9552, 9553, 9554, 9555, 9556, 9557, 9558, 9559, 9560, 9561, 9562, \n"
/usr/bin/printf "                         200120, 200121, 200122, 200123 ]"

}

exp_data_piminus12.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9303, 9304, 9305, 9306, 9307, 9308, 9309, 9310, 9311, 9312, 9313, 9314, 9315,  \n"
/usr/bin/printf "                         9355, 9356, 9357, 9358, 9359, 9360, 9361, 9362, 9363, 9364, 9365, 9366, 9367, \n"
/usr/bin/printf "                         200028, 200029, 200030, 200031 ]"

}

exp_data_piminus12.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 9407, 9408, 9409, 9410, 9411, 9412, 9413, 9414, 9415, 9416, 9417, 9418, 9419, \n"
/usr/bin/printf "                         9459, 9460, 9461, 9462, 9463, 9464, 9465, 9466, 9467, 9468, 9469, 9470, 9471, \n"
/usr/bin/printf "                         200076, 200077, 200078, 200079 ]"

}

exp_data_piminus12.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 9615, 9516, 9617, 9618, 9619, 9620, 9621, 9622, 9623, 9624, 9625, 9626, 9627, \n"
/usr/bin/printf "                         9667, 9668, 9669, 9670, 9671, 9672, 9673, 9674, 9675, 9676, 9677, 9678, 9679 ]"

}

exp_data_piminus12.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 9511, 9512, 9513, 9514, 9515, 9516, 9517, 9518, 9519, 9520, 9521, 9522, 9523, \n"
/usr/bin/printf "                         9563, 9564, 9565, 9566, 9567, 9568, 9569, 9570, 9571, 9572, 9573, 9574, 9575, \n"
/usr/bin/printf "                         200124, 200125, 200126, 200127 ]"

}

# ITEP771
#
# bid=73 (ITEP 5GeV/c pi-)

exp_data_piminus5.0GeV_C_ITEP() {

/usr/bin/printf "            DBRecords: [ 2130, 2131, 2132, 2133, 2135, 2136, 2137, 2138 ]"

}

exp_data_piminus5.0GeV_Cu_ITEP() {

/usr/bin/printf "            DBRecords: [ 2143, 2144, 2145, 2146, 2148, 2149, 2150, 2151 ]"

}

exp_data_piminus5.0GeV_Pb_ITEP() {

/usr/bin/printf "            DBRecords: [ 2152, 2153, 2154, 2155, 2156, 2157, 2158, 2159 ]"

}


#####################
# pi+ beam (piplus)
#####################

# HARP
# 
# bid=42-45 (3, 5, 8, 12 GeV/c pi+)

exp_data_piplus3.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9888, 9889, 9890, 9891, 9892, 9893, 9894, 9895, 9896, 9897, 9898, 9899, 9900, \n"
/usr/bin/printf "                         9940, 9941, 9942, 9943, 9944, 9945, 9946, 9947, 9948, 9949, 9950, 9951, 9952 ]"

}

exp_data_piplus3.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 9992, 9993, 9994, 9995, 9996, 9997, 9998, 9999, 10000, 10001, 10002, 10003, 10004, \n"
/usr/bin/printf "                         10044, 10045, 10046, 10047, 10048, 10049, 10050, 10051, 10052, 10053, 10054, 10055, 10056, \n"
/usr/bin/printf "                         200080, 200081, 200082, 200083 ]"

}

exp_data_piplus3.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10096, 10097, 10098, 10099, 10100, 10101, 10102, 10103, 10104, 10105, 10106, 10107, 10108, \n"
/usr/bin/printf "                         10148, 10149, 10150,        10152, 10153, 10154, 10155, 10156, 10157, 10158, 10159, 10160, \n"
/usr/bin/printf "                         200128, 200129, 200130, 200131 ]"
# do NOT use 10151 for now as it's messed up - there should be 3 data points, and there're 4, the last one being a duplicate
#   /usr/bin/printf "                         10148, 10149, 10150, 10151, 10152, 10153, 10154, 10155, 10156, 10157, 10158, 10159, 10160 ]"

}

exp_data_piplus5.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9901, 9902, 9903, 9904, 9905, 9906, 9907, 9908, 9909, 9910, 9911, 9912, 9913, \n"
/usr/bin/printf "                         9953, 9954, 9955, 9956, 9957, 9958, 9959, 9960, 9961, 9962, 9963, 9964, 9965 ]"

}

exp_data_piplus5.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10005, 10006, 10007, 10008, 10009, 10010, 10011, 10012, 10013, 10014, 10015, 10016, 10017, \n"
/usr/bin/printf "                         10057, 10058, 10059, 10060, 10061, 10062, 10063, 10064, 10065, 10066, 10067, 10068, 10069, \n"
/usr/bin/printf "                         200084, 200085, 200086, 200087 ]"

}

exp_data_piplus5.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 10213, 10214, 10215, 10216, 10217, 10218, 10219, 10220, 10221, 10222, 10223, 10224, 10225, \n"
/usr/bin/printf "                         10265, 10266, 10267, 10268, 10269, 10270, 10271, 10272, 10273, 10274, 10275, 10276, 10277 ]"

}

exp_data_piplus5.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10109, 10110, 10111, 10112, 10113, 10114, 10115, 10116, 10117, 10118, 10119, 10120, 10121, \n"
/usr/bin/printf "                         10161, 10162, 10163, 10164, 10165, 10166, 10167, 10168, 10169, 10170, 10171, 10172, 10173, \n"
/usr/bin/printf "                         200132, 200133, 200134, 200135 ]"

}

exp_data_piplus8.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9914, 9915, 9916, 9917, 9918, 9919, 9920, 9921, 9922, 9923, 9924, 9925, 9926, \n"
/usr/bin/printf "                         9966, 9967, 9968, 9969, 9970, 9971, 9972, 9973, 9974, 9975, 9976, 9977, 9978 ]"

}

exp_data_piplus8.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10018, 10019, 10020, 10021, 10022, 10023, 10024, 10025, 10026, 10027, 10028, 10029, 10030, \n"
/usr/bin/printf "                         10070, 10071, 10072, 10073, 10074, 10075, 10076, 10077, 10078, 10079, 10080, 10081, 10082, \n"
/usr/bin/printf "                         200088, 200089, 200090, 200091 ]"

}

exp_data_piplus8.0GeV_Ta_HARP() {
/usr/bin/printf "            DBRecords: [ 10226, 10227, 10228, 10229, 10230, 10231, 10232, 10233, 10234, 10235, 10236, 10237, 10238, \n"
/usr/bin/printf "                         10278, 10279, 10280, 10281, 10282, 10283, 10284, 10285, 10286, 10287, 10288, 10289, 10290 ]"
}

exp_data_piplus8.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10122, 10123, 10124, 10125, 10126, 10127, 10128, 10129, 10130, 10131, 10132, 10133, 10134, \n"
/usr/bin/printf "                         10174, 10175, 10176, 10177, 10178, 10179, 10180, 10181, 10182, 10183, 10184, 10185, 10186, \n"
/usr/bin/printf "                         200136, 200137, 200138, 200139 ]"

}

exp_data_piplus12.0GeV_C_HARP() {

/usr/bin/printf "            DBRecords: [ 9927, 9928, 9929, 9930, 9931, 9932, 9933, 9934, 9935, 9936, 9937, 9938, 9939,  \n"
/usr/bin/printf "                         9979, 9980, 9981, 9982, 9983, 9984, 9985, 9986, 9987, 9988, 9989, 9990, 9991 ]"

}

exp_data_piplus12.0GeV_Cu_HARP() {

/usr/bin/printf "            DBRecords: [ 10031, 10032, 10033, 10034, 10035, 10036, 10037, 10038, 10039, 10040, 10041, 10042, 10043, \n"
/usr/bin/printf "                         10083, 10084, 10085, 10086, 10087, 10088, 10089, 10090, 10091, 10092, 10093, 10094, 10095, \n"
/usr/bin/printf "                         200092, 200093, 200094, 200095 ]"

}

exp_data_piplus12.0GeV_Ta_HARP() {

/usr/bin/printf "            DBRecords: [ 10239, 10240, 10241, 10242, 10243, 10244, 10245, 10246, 10247, 10248, 10249, 10250,10251,  \n"
/usr/bin/printf "                         10291, 10292, 10293, 10294, 10295, 10296, 10297, 10298, 10299, 10300, 10301, 10302, 10303 ]"

}

exp_data_piplus12.0GeV_Pb_HARP() {

/usr/bin/printf "            DBRecords: [ 10135, 10136, 10137, 10138, 10139, 10140, 10141, 10142, 10143, 10144, 10145, 10146, 10147, \n"
/usr/bin/printf "                         10187, 10188, 10189, 10190, 10191, 10192, 10193, 10194, 10195, 10196, 10197, 10198, 10199, \n"
/usr/bin/printf "                         200140, 200141, 200142, 200143 ]"

}

# ITEP771
#
# bid=71-72 (3, 5 GeV/c pi+)

exp_data_piplus3.0GeV_C_ITEP() {

/usr/bin/printf "            DBRecords: [ 2184, 2185, 2186, 2187 ]"

}

exp_data_piplus3.0GeV_Cu_ITEP() {

/usr/bin/printf "            DBRecords: [ 2214, 2215, 2216, 2217 ]"

}

exp_data_piplus3.0GeV_Pb_ITEP() {

/usr/bin/printf "            DBRecords: [ 2243, 2244, 2245, 2246 ]"

}

exp_data_piplus5.0GeV_C_ITEP() {

/usr/bin/printf "            DBRecords: [ 2192, 2193, 2194, 2195, 2201 ]"

}

exp_data_piplus5.0GeV_Cu_ITEP() {

/usr/bin/printf "            DBRecords: [ 2222, 2223, 2224, 2225, 2231 ]"

}

exp_data_piplus5.0GeV_Pb_ITEP() {

/usr/bin/printf "            DBRecords: [ 2251, 2252, 2253, 2254, 2260 ]"

}

# NA61
#
# bid=96 

exp_data_piplus60.0GeV_C_NA61() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary K- \n"
#                                         NOTE: 200328 is for 100<theta<140 and has only 2 datapoints
#                                         200329-200332 are (reserved) for 140 through 360
#                                         but each has none or only 1 datapoint
#                                         so we do not use them
/usr/bin/printf "                         200324, 200325, 200326, 200327, 200328, \n"
/usr/bin/printf "                         // secondary K+ \n"
#                                         NOTE: 200338-200342 are (reserved) for 140 through 360
#                                         but each has only 1 datapoint 
#                                         so we're not using them
/usr/bin/printf "                         200333, 200334, 200335, 200336, 200337, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         200300, 200302, 200303, 200304, 200305, 200306, 200307, 200308, 200309, 200310, 200311, \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         200312, 200314, 200315, 200316, 200317, 200318, 200319, 200320, 200321, 200322, 200323 \n"
/usr/bin/printf "                       ] \n"

}



# SAS M6E
#
# bid=10 (11 for K+, 12 for proton)

exp_data_piplus100.0GeV_C_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         8964, 8965, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         8966, 8967, 8968, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         8969, 8970, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         8971, 8972, 8973, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         8974, 8975, \n"
/usr/bin/printf "                         // secondary antiproton \n"
/usr/bin/printf "                         8976, 8977, 8978 \n"
/usr/bin/printf "                       ] \n"
 
}

exp_data_piplus100.0GeV_Cu_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         8979, 8980, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         8981, 8982, 8983, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         8984, 8985, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         8986, 8987, 8988, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         8989, 8990, \n"
/usr/bin/printf "                         // secondary antiproton \n"
/usr/bin/printf "                         8991, 8992, 8993 \n"
/usr/bin/printf "                       ] \n"
 
}

exp_data_piplus100.0GeV_Pb_SASM6E() {

/usr/bin/printf "            DBRecords: [ \n"
/usr/bin/printf "                         // secondary pi+ \n"
/usr/bin/printf "                         8994, 8995, \n"
/usr/bin/printf "                         // secondary pi- \n"
/usr/bin/printf "                         8996, 8997, 8998, \n"
/usr/bin/printf "                         // secondary K+ \n"
/usr/bin/printf "                         8999, 9000, \n"
/usr/bin/printf "                         // secondary K- \n"
/usr/bin/printf "                         9001, 9002, 9003, \n"
/usr/bin/printf "                         // secondary proton \n"
/usr/bin/printf "                         9004, 9005, \n"
/usr/bin/printf "                         // secondary antiproton \n"
/usr/bin/printf "                         9006, 9007, 9008 \n"
/usr/bin/printf "                       ] \n"
 
}

