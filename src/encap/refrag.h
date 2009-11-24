/****************************************************************************/
/**
 *   @file          refrag.h
 *
 *          Project:     GSE LIBRARY
 *
 *          Company:     THALES ALENIA SPACE
 *
 *          Module name: REFRAGMENTATION
 *
 *   @brief         GSE refragmentation
 *
 *   @author        Julien BERNARD / Viveris Technologies
 *
 */
/****************************************************************************/


#ifndef GSE_REFRAG_H
#define GSE_REFRAG_H

#include <stdint.h>

#include "virtual_buffer.h"

/****************************************************************************
 *
 *   FUNCTION PROTOTYPES
 *
 ****************************************************************************/

/**
 *  @brief   Refragment a GSE packet packet1 in two new GSE packets (packet[1, 2])
 *
 *  For the first new GSE packet, header offset will depend on offsets applied
 *  on packet1 creation with \ref gse_encap_get_packet or \ref
 *  gse_encap_get_packet_copy functions.\n
 *  In the case of input GSE packet carrying a fragment of PDU, the QoS value
 *  is only used to check the Frag Id validity. If the GSE packet carries a
 *  complete PDU, the QoS value is used as Frag Id for the two new created
 *  fragments.
 *
 *  @warning The first fragment length can be smaller than the max_length
 *           given as parameter.
 *  @warning In case of error, the packet given as parameter is reinitialized.
 *
 *  @param   packet1       IN: The GSE packet to refragment
 *                         OUT: The first GSE fragment
 *  @param   packet2       OUT: The second GSE fragment on success,
 *                              NULL in case of error
 *  @param   head_offset   The offset to apply at the beginning of the created
 *                         fragment (packet2)
 *  @param   trail_offset  The offset to apply at the end of the created fragment
 *  @param   qos           The QoS associated to the wanted GSE packet
 *  @param   max_length    Maximum length of the first new GSE packet (in bytes)
 *
 *  @return
 *                         - success/informative code among:
 *                           - \ref GSE_STATUS_OK
 *                         - warning/error code among:
 *                           - \ref GSE_STATUS_NULL_PTR
 *                           - \ref GSE_STATUS_LENGTH_TOO_HIGH
 *                           - \ref GSE_STATUS_LENGTH_TOO_SMALL
 *                           - \ref GSE_STATUS_REFRAG_UNNECESSARY
 *                           - \ref GSE_STATUS_INVALID_GSE_LENGTH
 *                           - \ref GSE_STATUS_INVALID_LT
 *                           - \ref GSE_STATUS_INTERNAL_ERROR;
 *                           - \ref GSE_STATUS_INVALID_HEADER
 *                           - \ref GSE_STATUS_PTR_OUTSIDE_BUFF
 *                           - \ref GSE_STATUS_FRAG_PTRS
 *                           - \ref GSE_STATUS_BUFF_LENGTH_NULL
 *                           - \ref GSE_STATUS_MALLOC_FAILED
 *                           - \ref GSE_STATUS_MULTIPLE_VBUF_ACCESS
 *                           - \ref GSE_STATUS_DATA_TOO_LONG
 *                           - \ref GSE_STATUS_PTR_OUTSIDE_BUFF
 *                           - \ref GSE_STATUS_FRAG_PTRS
 *                           - \ref GSE_STATUS_INVALID_QOS
 */
gse_status_t gse_refrag_packet(gse_vfrag_t *packet1, gse_vfrag_t **packet2,
                               size_t head_offset, size_t trail_offset,
                               uint8_t qos, size_t max_length);

#endif