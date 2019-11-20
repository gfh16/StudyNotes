*************************************************************************
c      ver. 1.0 E. De Filippo dapnia-sphn (1994)     INDRAloss
c      Modified by L. Nalpas              (1996)
c      Modified by E. De Filippo          (1997)
c      Modified by R. Dayras              (1997)
c      ultima rev. 2/1999   e.d.f. 
c      versione standard sun, ibm, alpha (unix), alpha (vms)
c      versione FORTRAN90 -->          ask to e.d.f. if interested
c      versione per windows NT/98/95   ask to e.d.f. if interested           
c      DAPNIA/Saclay
c      revision  03/05  e.d.f.
*************************************************************************
 
       subroutine LOSS_INIT(inp1,path,icode)
c      iniatialize the program loss to the default values
c      of the INDRA detector
       implicit real*8(a-h,o-z)
       integer i,j
       character*80  namefil
       character*(*) path
       character  mate_name*20
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       data RPP/623.61040/
 
       
       icode = 0       
       j=1
       do i=1,20
        iaddress(i,1) = j
	iaddress(i,2) = j+99
	j=j+100
       enddo
       
        
       mate_name(1)    =  'Si'
       tmate_type(1,1) =    1
       tmate_type(1,2) =    1
       tmate_type(1,3) =  300.0 * 0.233          ! mg/cm^2   
       tmate_type(1,4) =    0

       mate_name(2)    =  'Mylar'
       tmate_type(2,1) =    2
       tmate_type(2,2) =    1
       tmate_type(2,3) =   2.5  * 0.1395         ! mg/cm^2   
       tmate_type(2,4) =    0

       mate_name(3)    =  'NE102'                 
       tmate_type(3,1) =    3
       tmate_type(3,2) =    1
       tmate_type(3,3) =   500. * 0.1032         ! mg/cm^2   
       tmate_type(3,4) =    0
 
       mate_name(4)    =  'Ni'                 
       tmate_type(4,1) =    4
       tmate_type(4,2) =    2
       tmate_type(4,3) =   0.2                   ! mg/cm^2   
       tmate_type(4,4) =    0
 
       mate_name(5)    =  'C3F8'                 
       tmate_type(5,1) =    5
       tmate_type(5,2) =   -1
       tmate_type(5,3) =    50. / 1.3333          !torr 
       tmate_type(5,4) =    50.                   !mm of gaz  
       tmate_type(5,5) =    188.                  !Molecula Weight
       tmate_type(5,6) =    19. + 273.15          !temperature (k)
       press = tmate_type(5,3)
       tmate_type(5,3) = (tmate_type(5,5) *
     # press * tmate_type(5,4))/
     #  (RPP*tmate_type(5,6))
 
       mate_name(6)    =  'C'                 
       tmate_type(6,1) =    6
       tmate_type(6,2) =    2
       tmate_type(6,3) =   0.20                 ! mg/cm^2   
       tmate_type(6,4) =    0
 
       mate_name(7)    =  'Ag'                 
       tmate_type(7,1) =    7
       tmate_type(7,2) =    2
       tmate_type(7,3) =   0.20                 ! mg/cm^2   
       tmate_type(7,4) =    0
 
       mate_name(8)    =  'Sn'                 
       tmate_type(8,1) =    8
       tmate_type(8,2) =    2
       tmate_type(8,3) =   0.20                   ! mg/cm^2   
       tmate_type(8,4) =    0
 
       mate_name(9)    =  'CsI'                 
       tmate_type(9,1) =    9
       tmate_type(9,2) =    3
       tmate_type(9,3) =   10.0 * 4510.0          ! mg/cm^2   
       tmate_type(9,4) =    0
 
       mate_name(10)    =  'Au'                 
       tmate_type(10,1) =   10
       tmate_type(10,2) =    2
       tmate_type(10,3) =   0.20                   ! mg/cm^2   
       tmate_type(10,4) =    0
 
       mate_name(11)    =  'U'                 
       tmate_type(11,1) =    11
       tmate_type(11,2) =    2
       tmate_type(11,3) =   0.20                   ! mg/cm^2   
       tmate_type(11,4) =    0
 
       mate_name(12)    =  'Al'                 
       tmate_type(12,1) =    12
       tmate_type(12,2) =    2
       tmate_type(12,3) =   0.20                   ! mg/cm^2   
       tmate_type(12,4) =    0
 
       mate_name(13)    =  'x13'                 
       tmate_type(13,1) =    13
       tmate_type(13,2) =    2
       tmate_type(13,3) =   0.20                 ! mg/cm^2   
       tmate_type(13,4) =    0
 
       mate_name(14)    =  'x14'                 
       tmate_type(14,1) =    14
       tmate_type(14,2) =    2
       tmate_type(14,3) =   0.20                 ! mg/cm^2   
       tmate_type(14,4) =    0
 
       mate_name(15)    =  'X15'                 
       tmate_type(15,1) =    15
       tmate_type(15,2) =    1
       tmate_type(15,3) =   0.20                 ! mg/cm^2   
       tmate_type(15,4) =    0
 
       mate_name(16)    =  'X16'                 
       tmate_type(16,1) =    16
       tmate_type(16,2) =    2
       tmate_type(16,3) =   0.20                 ! mg/cm^2   
       tmate_type(16,4) =    0
   
       mate_name(17)    =  'x17'                 
       tmate_type(17,1) =    17
       tmate_type(17,2) =    1
       tmate_type(17,3) =   0.20                 ! mg/cm^2   
       tmate_type(17,4) =    0
 
       mate_name(18)    =  'x18'                 
       tmate_type(18,1) =    18
       tmate_type(18,2) =    2
       tmate_type(18,3) =   0.20                 ! mg/cm^2   
       tmate_type(18,4) =    0
 
       mate_name(19)    =  'Pb'                 
       tmate_type(19,1) =    19
       tmate_type(19,2) =    2
       tmate_type(19,3) =   0.20                 ! mg/cm^2   
       tmate_type(19,4) =    0
 
       mate_name(20)    =  'x20'                 
       tmate_type(20,1) =    20
       tmate_type(20,2) =    2
       tmate_type(20,3) =   0.20                 ! mg/cm^2   
       tmate_type(20,4) =    0

c  on ecrit le path de namefil en "dur" car ces routines peuvent etre utilisees
c  dans un environnement different de VEDA ou vedafil(1:long_path) n'existe pas

       namefil=path//'loss1.vedasac'
       write(*,*)'Open energy loss_file: ',trim(namefil)
       open(unit = inp1, file = namefil,
     #     iostat=ios, status='old')
       if(ios.ne.0)then
        icode=7
        return
       endif

	do k=1,20
	read(inp1,*) zr(k),ar(k)
         do j=iaddress(k,1), iaddress(k,2)
          read(inp1,*)(coeff(i,j),i=1,14)
         end do
	end do
       close(inp1)
       return

       end
 
       subroutine SET_THICKNESS(thick,amasr,id)
c	New argument amasr (01/09/97)
c      set the current thickness values
       implicit real*8(a-h,o-z)
       character  mate_name*20
       dimension density(20)
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
c Density in (g/cc)/10
c For gas: -density=4/3 (conversion torr to mb)
C          -thick=pressure (mb)
C          -RPP=0.01*P0*V0/T0  P0=760 torr, V0=22413 cm**3 T0=273.15 K      
       data density /0.233, 0.1395, 0.1032, 0.8902, 1.3333, 0.190,
     # 1.05, 0.713, 0.451, 1.93,1.895, 0.270, 0.0, 0.0, 0.0, 0.0, 0.0, 
     # 0.0, 1.135, 0.0/
       data RPP/623.61040/
       
       if(amasr.eq.0.0)then 
        amas=ar(id) 
       else
        amas = amasr
       endif      
       if(tmate_type(id,2).eq.1) tmate_type(id,3)=thick*density(id)*
     # ar(id)/amas
       if(tmate_type(id,2).eq.-1) tmate_type(id,3)=(tmate_type(id,5)
     #  *(thick/density(id))*tmate_type(id,4))/
     #  (RPP*tmate_type(id,6))
       if(tmate_type(id,2).eq.2) tmate_type(id,3)=thick*ar(id)/amas
       if(tmate_type(id,2).eq.3) tmate_type(id,3)=thick*density(id)*
     # 10000.0*ar(id)/amas
 
       return
       end
 
       subroutine GET_THICKNESS(thick,amasr,id)
c	New argument amasr (01/09/97)
c      Get the current thickness values or pression
       implicit real*8(a-h,o-z)
       character  mate_name*20
       dimension density(20)
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       data density /0.233, 0.1395, 0.1032, 0.8902, 1.3333, 0.190,
     # 1.05, 0.713, 0.451, 1.93,1.895, 0.270, 0.0, 0.0, 0.0, 0.0, 0.0, 
     # 0.0, 1.135, 0.0/
       data RPP/623.61040/
 
	if(amasr.eq.0.0) amasr=ar(id)       
       if(tmate_type(id,2).eq.1) thick=tmate_type(id,3)*amasr/
     # ar(id)/density(id)
       if(tmate_type(id,2).eq.-1) thick=(RPP*tmate_type(id,6)*
     # tmate_type(id,3))/(tmate_type(id,5)*tmate_type(id,4))*
     # density(id)
       if(tmate_type(id,2).eq.2) thick=tmate_type(id,3)*amasr/ar(id)
       if(tmate_type(id,2).eq.3) thick=tmate_type(id,3)*amasr/
     # ar(id)/density(id)/10000.0 

       return
       end
 
       subroutine SET_TEMP_GAZ(temp,id)
       implicit real*8 (a-h,o-z)
       character mate_name*20
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
 
       if(tmate_type(id,2).eq.-1)then
        tmate_type(id,6) = temp + 273.15
        write(*,10)mate_name(id),temp
       endif
10     format('Gaz ',a5,'temperature set to ',f5.1,' C')
       return
       end
 

*****************************************************************************
*      INDRAloss library      (modifie:  R.Dayras & E.de FILIPPO 24/5/96)   *
*                             (last modified:  R. Dayras      1/9/97        *
*                             (old version in vedasac.f_old)                *
*****************************************************************************
      
       subroutine DELTA(ede,az,am,mate,EIN,ERE,ITER,
     #                EIN1,ERE1,ITER1,eps,icode)
c      calculate the incident energy for a given 
c      material knowing the DeltaE
      
       implicit real*8(a-h,o-z) 
       parameter (idirect=1, inverse=2, jmax=100)  
       character  mate_name*20
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       
       integer*4 nbloc,nnevt,nevt,nevtot,ngene,numrun
        
       Common /STATEVT/nbloc,nnevt,nevt,nevtot,ngene,numrun
       Common /toto/ii
       
       icode = 0
       EIN=0
       ERE=0
       EIN1=0
       ERE1=0   
       iter = 1
       eres = 0.0001 * am 
       idr = inverse 
       call PARAM(eres,az,am,mate,ed,ei,idr,icode)
       if(icode.eq.3)then
        return
       endif
c       if(ede.gt.ed)then 
c        icode=1
c        return 
c       endif
       e1 = ed
       if(az.eq.1)then 
         e2 = 400. * am
       elseif(az.ge.2)then 
         e2 = 200. * am 
       endif
       idr   = idirect
       en = abs(e2 - e1) /2.0 + e1
       call FAST_PARAM(en,az,am,mate,dcalc,eres,idr,icode)
       do j=1,jmax
         diff = dcalc - ede
         difa = abs(diff)
         if(difa.lt.eps)then
          goto 10
         elseif(diff.lt.0.)then
          e2 = en
         elseif(diff.gt.0.)then
          e1 = en
         endif
         en = abs(e2 - e1) /2.0 + e1
         iter = iter + 1
c        param is called faster without charging parameters
c        that are always the same in the iteration procedure
         call FAST_PARAM(en,az,am,mate,dcalc,eres,idr,icode) !entryparam
        enddo
5      continue 
       icode=2
       return
10     continue 
       EIN = en 
       ERE  = en - ede
C
c      recherche de la deuxieme solution le 23/05/96
c
c  Modif du 18/05/00 : la 2de solution n'est recherche que si
c    DE > a l'energie d'arret dans le milieu
C
       if(ede.gt.ed) then
C
       e1 = ed
       e2 = ein 
       iter1=0
       idr   = idirect
       en = abs(e2 - e1) /2.0 + e1
       call FAST_PARAM(en,az,am,mate,dcalc,eres,idr,icode)
       do j=1,jmax
         diff = dcalc - ede
         difa = abs(diff)
         if(difa.lt.eps)then
          goto 20
         elseif(diff.gt.0.)then
          e2 = en
         elseif(diff.lt.0.)then
          e1 = en
         endif
         en = abs(e2 - e1) /2.0 + e1
         iter1 = iter1 + 1
c        param is called faster without charging parameters
c        that are always the same in the iteration procedure
         call FAST_PARAM(en,az,am,mate,dcalc,eres,idr,icode) !entryparam
        enddo
c  Modif du 18/05/00
       endif
C
       icode=0
       return
20     continue 
       EIN1 = en 
       ERE1  = en - ede
       return 
       end
      
       subroutine PARAM(einp,az,am,id,EL,ER,idirec,ICODE)
      
c      **************************************************
c         calculation of energy loss in a given 
c              material by polynomial fit
c      ************************************************** 
c      input   einp,az,am,mate,direc [idirect,inverse]
c      output  EL (energy loss) ER (Res. energy | Inc. energy)
c      call    function eloss
      
       parameter (istout=6) 
       implicit real*8(a-h,o-z) 
       character mate_name*20
      
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       common/los/vect(15),perc,ratio
        
       integer*4 nbloc,nnevt,nevt,nevtot,ngene,numrun
        
       Common /STATEVT/nbloc,nnevt,nevt,nevtot,ngene,numrun
       Common /toto/ii
       
       PERC = 0.02
       icode = 0     
       vect(15) = tmate_type(id,3) 
       call GET_PARAM(id,amasr,az,icode) 
       if(icode.ne.0)then
        return
       endif
    
c      fast entry (for iterative procedures)
       ENTRY FAST_PARAM(einp,az,am,id,EL,ER,idirec,ICODE)
       ER = eloss(einp,am,idirec)
       
       if (idirec.eq.1)then
         EL = einp - er
         if (EL.lt.0.005)then
          EL=0.0
          ER=einp
         endif   
       else
         EL = ER - einp
       end if  
       
       return
c      end param
       end   !subroutine param
      
      
       subroutine GET_PARAM(id,amasr,az,ICODE)
c	New argument amasr (01/09/97)
       implicit real*8(a-h,o-z)
       character mate_name*20
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       common/los/vect(15),perc,ratio
       common/estrapo/adm,adn,arm
      
       index = id
	if(amasr.eq.0.0) amasr=ar(id)
       ind = iaddress(index,1) + az - 1
       if ((az.eq.coeff(1,ind)).and.
     #     (ind.le.iaddress(index,2))) then
	ratio=amasr/ar(id) 
        do j=1,14
          vect(j) = coeff(j,ind)
        end do
       else
        icode = 3
        return    
       end if 
       
       
       x1 = log(0.1) 
       x2 = log(0.2) 
       ran= 0.0
       do j= 2,6
         ran = ran + vect(j+2) * x2**(j-1) 
       end do
       ran = ran + vect(3) 
       y2 = ran 
       ran= 0.0
       do j= 2,6
         ran = ran + vect(j+2) * x1**(j-1) 
       end do
       ran = ran + vect(3) 
       y1 = ran 
       adm=(y2-y1)/(x2-x1)
       adn=(y1-adm*x1)
       arm = y1
       return
       end
       
       function ELOSS(einp,am,idirec)
c      ***********************************************
c      called by PARAM
c      ***********************************************
       implicit real*8(a-h,o-z)
       common/los/vect(15),perc,ratio
       common/estrapo/adm,adn,arm
       
       integer*4 nbloc,nnevt,nevt,nevtot,ngene,numrun
        
       Common /STATEVT/nbloc,nnevt,nevt,nevtot,ngene,numrun
       
       if(einp.le.0.)then
         if (idirec.eq.1) then
           eloss = 0.
         else
           eloss = -1.
         end if
         goto 100
       end if

       eps   =  einp/am
       dleps =  dlog(eps)
       riso  =  dlog(am/vect(2))

       if(eps.lt.0.1)then 
        ran = adm*dleps+adn
       else
        ran= 0.0
        do j= 2,6
         ran = ran + vect(j+2) * dleps**(j-1) 
        end do
        ran = ran + vect(3)
       endif 
       ran=ran+riso       

       range = dexp(ran)
c      if(idirec.eq.1)type*,eps,range    !test range
       if(idirec.eq.1) then       
        range = range - vect(15)
        if (range.le.0.005) then
          eloss = 0.
          goto 100
        end if
       else
        range = range + vect(15)
       end if

       ranx = dlog(range)
       ranx1 = ranx - riso

       if(ranx1.lt.arm)then 
        depsx = (ranx1-adn)/adm
       else
       depsx = 0.0
       do j=2,6
         depsx = depsx+ vect(j+8)*ranx1**(j-1)
       end do
       depsx = depsx + vect(9)
       endif

       eps1 = depsx + dlog(1-perc)     
       eps2 = depsx + dlog(1+perc)
       rap = dlog ((1+perc)/(1-perc))
   
       rn1=0.0
       if( dexp(eps1).lt.0.1)then 
        rn1 = adm*eps1+adn
       else
       do j= 1,6
        rn1 = rn1 + vect(j+2) * eps1**(j-1) 
       end do
       endif
       rn2=0.0
       if( dexp(eps2).lt.0.1)then 
        rn2 = adm*eps2+adn
       else
       do j= 1,6
        rn2 = rn2 + vect(j+2) * eps2**(j-1) 
       end do
       endif
       epres = eps1 + (rap/(rn2-rn1)) * (ranx1-rn1)
       epres = dexp(epres)

       eloss = am*epres 
     
100    continue
       return
c      end eloss
       end    !function eloss
       

       subroutine RANGE(einc,az,am,id,amasr,RANG,ICODE)
c	New argument amasr (01/09/97)
c      calculate the range for a given energy
c      and mass of the incident particle  

       implicit real*8(a-h,o-z)
       common/los/vect(15),perc,ratio
       common/estrapo/adm,adn,arm

       icode = 0 
       call GET_PARAM(id,amasr,az,icode)
       if(icode.ne.0)then
        return
       endif 
       if(einc.le.0.)then
        rang = 0.
        return
       endif 
       eps   =  einc/am
       dleps =  dlog(eps)
       riso  =  dlog(am/vect(2))

       if(eps.lt.0.1)then 
        ran = adm*dleps+adn
       else
        ran= 0.0
        do j= 2,6
         ran = ran + vect(j+2) * dleps**(j-1) 
        end do
        ran = ran + vect(3)
       endif 
       ran=ran+riso
       RANG = ratio*dexp(ran)
       return    
       end

       Subroutine Set_Gaz_Param(temp,epes,id)
       implicit real*8 (a-h,o-z)
       character  mate_name*20
       common /main/coeff(14,2000),iaddress(20,2),tmate_type(20,6),
     #              mate_name(20),zr(20),ar(20)
       if(tmate_type(id,2).eq.-1)then   !it is a gaz
        tmate_type(id,4) = epes
        tmate_type(id,6) = temp + 273.15
       endif
       return
       end


       subroutine ERROR_CODE(iw,icode)
       character*80 code(0:10)

       if(icode.ge.10)icode=10
       code(0) = ' OK'
       code(1) = ' Error: The particle stops in the detector'
       code(2) = ' Error: Too many iterations or energy out of range'
       code(3) = ' Error module PARAM: Z not found '
       code(5) = ' Error open input file'
       code(6) = ' Error read from input-data file'
       code(7) = ' Error open data file'
       code(10)= ' *** Error *** '
       write(iw,'(a)')code(icode)
       return
       end


       subroutine EXITP
c      exit the program
       stop
       end
****************** end indraloss library *************************




 

 
 
 
 
 
 
 
