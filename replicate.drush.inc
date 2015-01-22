<?php
/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {

  $items['replicate'] = array(
    'description' => 'Replicate an Enitity via Drush!',
    'arguments' => array(
      'entity-type' => dt('Type of Entity (eg. Node) that you wish to replicate'),
    ),
    'arguments' => array(
      'id-number' => dt('ID value of the specified Entity Type (eg. NodeID'),
    ),
    'aliases' => array('rep'),
    'examples' => array(
      'drush replicate node 1' =>
        'Node 1 is replicated via drush using full command',
      'drush rep node 1' =>
        'Node 1 is replicated via drush using aliased command',
    ),
  );
  return $items;
}
/**
 * Callback for the drush-demo-command command
 */
function demo_replicate_replicate() {
  drupal_set_message(t('Hello world!'));








}
/**
 * Replicate the entity corresponding to the type and id passed in argument and save it.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int $id
 *   The unique entity identifier.
 *
 * @return mixed
 *   The newly created entity id if the clone has been created and saved,
 *   else FALSE.
 *
 * @see replicate_entity()
 */
function replicate_entity_by_id($entity_type, $id) {
  $original = entity_load_single($entity_type, $id);
  return replicate_entity($entity_type, $original);
}
/**
 * Replicate the entity passed in argument and save it.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to replicate.
 *
 * @return mixed
 *   The newly created entity id if the clone has been created and saved,
 *   else FALSE.
 */
function replicate_entity($entity_type, $entity) {
  $clone = replicate_clone_entity($entity_type, $entity);
  if ($clone) {
    entity_save($entity_type, $clone);
      list($entity_id) = entity_extract_ids($entity_type, $clone);

    if (isset($entity_id)) {
      return $entity_id;
    }
  }

  return FALSE;
}
