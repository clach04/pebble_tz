#!/usr/bin/env python
# -*- coding: utf8 -*-
# vim:ts=4:sw=4:softtabstop=4:smarttab:expandtab
#

all_zones =  [
    '-12:00',
    '-11:00',
    '-10:00',
    '-09:30',
    '-09:00',
    '-08:00',
    '-07:00',
    '-06:00',
    '-05:00',
    '-04:30',
    '-04:00',
    '-03:30',
    '-03:00',
    '-02:00',
    '-01:00',
    ' 00:00', # '±00:00',
    '+01:00',
    '+02:00',
    '+03:00',
    '+03:30',
    '+04:00',
    '+04:30',
    '+05:00',
    '+05:30',
    '+05:45',
    '+06:00',
    '+06:30',
    '+07:00',
    '+08:00',
    '+08:30',
    '+08:45',
    '+09:00',
    '+09:30',
    '+09:45',
    '+10:00',
    '+10:30',
    '+11:00',
    '+12:00',
    '+12:45',
    '+13:00',
    '+14:00',
]

for zone in all_zones:
    #print('UTC%s' % zone)
    hours, mins = zone.split(':')
    #print('\t%r' % zone.split(':'))
    #print('\t%r' % ((hours, mins),))
    hours = int(hours)
    mins = int(mins)
    offset = hours * 60 + mins  # offset in minutes
    #print('\t%r' % ((hours, mins),))
    #print('\t%r' % offset)
    
    print('{"label": "%s", "value": "%d" },' % (zone, offset))
    
