/**
 *  @file   PandoraPFANew/include/Objects/Cluster.h
 * 
 *  @brief  Header file for the cluster class.
 * 
 *  $Log: $
 */
#ifndef CLUSTER_H
#define CLUSTER_H 1

#include "Api/PandoraContentApi.h"

#include "Objects/OrderedCaloHitList.h"

#include "Pandora/PandoraInternal.h"

namespace pandora
{

class CaloHit;

//------------------------------------------------------------------------------------------------------------------------------------------
    
/**
 *  @brief  Cluster class
 */
class Cluster
{
public:
    /**
     *  @brief  Get the ordered calo hit list
     * 
     *  @return Address of the ordered calo hit list
     */    
    const OrderedCaloHitList &GetOrderedCaloHitList() const;

    /**
     *  @brief  Get the list of tracks associated with the cluster
     * 
     *  @return Address of the list of associated tracks
     */
    const TrackList &GetAssociatedTrackList() const;

    /**
     *  @brief  Get calo hits in specified pseudo layer
     * 
     *  @param  pseudoLayer the pseudo layer
     *  @param  pCaloHitList to receive the address of the relevant calo hit list
     */
    StatusCode GetCaloHitsInPseudoLayer(const PseudoLayer pseudoLayer, CaloHitList *&pCaloHitList) const;

private:
    /**
     *  @brief  Constructor
     * 
     *  @param  pCaloHit address of calo hit with which initialize cluster
     */
    Cluster(CaloHit *pCaloHit);

    /**
     *  @brief  Constructor
     * 
     *  @param  pCaloHitList calo hits with which to create cluster
     */
    Cluster(InputCaloHitList *pCaloHitList);

    /**
     *  @brief  Constructor
     * 
     *  @param  pTrack address of track with which to seed cluster
     */
    Cluster(Track *pTrack);

    /**
     *  @brief  Destructor
     */
    ~Cluster();

    /**
     *  @brief  Add a calo hit to the cluster
     * 
     *  @param  pCaloHit the address of the calo hit
     */
    StatusCode AddCaloHit(CaloHit *const pCaloHit);

    /**
     *  @brief  Add the calo hits from a second cluster to this
     * 
     *  @param  pCluster the address of the second cluster
     */
    StatusCode AddHitsFromSecondCluster(Cluster *const pCluster);

    /**
     *  @brief  Add an association between the cluster and a track
     * 
     *  @param  pTrack the address of the track with which the cluster is associated
     */
    StatusCode AddTrackAssociation(Track *const pTrack);

    /**
     *  @brief  Remove an association between the cluster and a track
     * 
     *  @param  pTrack the address of the track with which the cluster is no longer associated
     */
    StatusCode RemoveTrackAssociation(Track *const pTrack);

    OrderedCaloHitList      m_orderedCaloHitList;       ///< The ordered calo hit list

    TrackList               m_associatedTrackList;      ///< The list of tracks associated with the cluster

    friend class PandoraContentApiImpl;
    friend class ClusterManager;
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline const OrderedCaloHitList &Cluster::GetOrderedCaloHitList() const
{
    return m_orderedCaloHitList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Cluster::GetAssociatedTrackList() const
{
    return m_associatedTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline StatusCode Cluster::GetCaloHitsInPseudoLayer(const PseudoLayer pseudoLayer, CaloHitList *&pCaloHitList) const
{
    return m_orderedCaloHitList.GetCaloHitsInPseudoLayer(pseudoLayer, pCaloHitList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline StatusCode Cluster::AddCaloHit(CaloHit *const pCaloHit)
{
    return m_orderedCaloHitList.AddCaloHit(pCaloHit);
}

} // namespace pandora

#endif // #ifndef CLUSTER_H
