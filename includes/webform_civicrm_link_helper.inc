<?php
/*
 * @author Klaas Eikelboom  <klaas.eikelboom@civicoop.org>
 * @date 17-Aug-2020
 * @license  AGPL-3.0
 */

class webform_civicrm_link_helper {

  static $instance = NULL;

  /**
   * webform_civicrm_link_helper constructor.
   */
  public function __construct() {
  }

  static function instance() {
    if (!isset(self::$instance)) {
      self::$instance = new webform_civicrm_link_helper();
    }
    return self::$instance;
  }

  public function insertSubmissions($nid) {
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    $result = db_query('select sid from {webform_submissions} where nid=:nid', [':nid' => $nid]);
    foreach ($result as $row) {
      $submission = webform_get_submission($nid, $row->sid);
      $this->updateSubmission($submission);
    }
  }

  /**
   * @param $submission
   *
   * @throws \Exception
   */
  public function updateSubmission($submission) {
    if (!empty($submission->civicrm)) {
      db_delete('webform_civicrm_links')
        ->condition('sid', $submission->sid)
        ->execute();
      foreach ($submission->civicrm as $name => $entities) {
        foreach ($entities as $sequence => $entity) {
          db_insert('webform_civicrm_links')
            ->fields([
              'sid' => $submission->sid,
              'entity_table' => $name,
              'sequence' => $sequence,
              'entity_id' => $entity['id']
            ])
            ->execute();
        }
      }
    }
  }

  public function enabled($nid) {
    return $enabled = db_query('select enabled from {webform_civicrm_links_config} where nid = :nid', [
      ':nid' => $nid,
    ])->fetchField();
  }

  public function webforms() {
    return db_query('select n.nid, n.title from {node} n
                     where n.nid in (select f.nid from {webform_civicrm_links_config} f where enabled=1)')
      ->fetchAllKeyed();
  }

}
